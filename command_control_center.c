/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/30 20:00:00 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_input(t_cmd *cmd)
{
	int	fd;

	if (cmd->input)
	{
		fd = open(cmd->input, O_RDONLY);
		if (fd == -1)
			return (ft_putstr_fd("bash: ", 2), perror(cmd->input), -1);
		(dup2(fd, STDIN_FILENO), close(fd));
	}
	if (apply_heredoc(cmd) == -1)
		return (-1);
	return (0);
}

int	apply_output(t_cmd *cmd)
{
	int	fd;

	if (cmd->output)
	{
		fd = open(cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd == -1)
			return (ft_putstr_fd("bash: ", 2), perror(cmd->output), -1);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	if (cmd->output_append)
	{
		fd = open(cmd->output_append, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (fd == -1)
			return (ft_putstr_fd("bash: ", 2), perror(cmd->output_append), -1);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	if (cmd->output_rank && cmd->output_rank < cmd->input_rank)
	{
		if (apply_output(cmd) == -1)
			return (-1);
		return (apply_input(cmd));
	}
	if (apply_input(cmd) == -1)
		return (-1);
	return (apply_output(cmd));
}

static int	dispatch_builtin(t_cmd *cmd, t_shell *shell, t_token *tokens)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd->args[1], &shell->env, cmd->args, &shell->exit_status);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		(ft_echo(cmd->args), shell->exit_status = 0);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		(ft_env(shell->env), shell->exit_status = 0);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(shell->exit_status, tokens, cmd, *shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ft_export(&shell->env, cmd->args, &shell->exit_status);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		(ft_pwd(shell->env, cmd->args), shell->exit_status = 0);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		(ft_unset(&shell->env, cmd->args[1]), shell->exit_status = 0);
	else
		return (0);
	return (1);
}

void	dispatch_command(t_cmd *com_to_exec,
							t_shell *shell, t_token *tokens)
{
	if (!com_to_exec->args[0])
		return ;
	if (dispatch_builtin(com_to_exec, shell, tokens))
		return ;
	if (ft_is_execute(com_to_exec->args[0], shell->env) == 2)
		return (ft_path_exec(com_to_exec->args[0], shell,
				com_to_exec->args, 0));
	if (ft_is_execute(com_to_exec->args[0], shell->env) == 1)
		return (ft_exec(com_to_exec->args[0], com_to_exec->args, shell));
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(com_to_exec->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
}

void	command_control(t_cmd *com_to_exec,
							t_shell *shell, t_token *tokens)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(com_to_exec) == -1)
	{
		shell->exit_status = 1;
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	dispatch_command(com_to_exec, shell, tokens);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	ft_is_execute(char *str, t_env *first_env)
{
	t_env	*parseur;
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	parseur = first_env;
	while (parseur)
	{
		if (ft_strncmp(parseur->name, "PATH", 5) == 0)
		{
			path = ft_split (parseur->value, ':');
			while (path[i])
			{
				tmp = ft_strjoin(path[i], "/");
				path[i] = ft_strjoin(tmp, str);
				if (access(path[i], X_OK) == 0)
					return (2);
				i++;
			}
		}
		parseur = parseur->next;
	}
	if ((str[0] == '.' && str[1] == '/') || (str[0] == '/')) 
		return (1);
	return (0);
}

void	ft_path_exec(char *str, t_shell *shell, char **args, int i)
{
	t_env	*parseur;
	char	**path;
	char	**envp;
	char	*tmp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0 && i == 0)
	{
		parseur = shell->env;
		i = 0;
		while (parseur)
		{
			if (ft_strncmp(parseur->name, "PATH", 5) == 0)
			{
				envp = ft_envp(shell->env);
				path = ft_split (parseur->value, ':');
				while (path[i])
				{
					tmp = ft_strjoin(path[i], "/");
					path[i] = ft_strjoin(tmp, str);
					if (execve(path[i], args, envp) != -1)
    					exit(EXIT_FAILURE);
					i++;
				}
			}
			parseur = parseur->next;
		}
		exit(127);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		shell->exit_status = wait_status_to_code(status);
	}
	if (pid < 0)
		perror("error");
}
