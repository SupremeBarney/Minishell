/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center_second.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 14:46:33 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_execute_two(char *str)
{
	if ((str[0] == '.' && str[1] == '/') || (str[0] == '/'))
		return (1);
	return (0);
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
	return (ft_is_execute_two(str));
}

void	ft_path_exec_two(char *str, t_shell *shell, char **args, t_var *var)
{
	int		i;
	char	**path;
	char	**envp;

	var->parseur = shell->env;
	i = 0;
	while (var->parseur)
	{
		if (ft_strncmp(var->parseur->name, "PATH", 5) == 0)
		{
			envp = ft_envp(shell->env);
			path = ft_split (var->parseur->value, ':');
			while (path[i])
			{
				var->tmp = ft_strjoin(path[i], "/");
				path[i] = ft_strjoin(var->tmp, str);
				if (execve(path[i], args, envp) != -1)
					exit(EXIT_FAILURE);
				i++;
			}
		}
		var->parseur = var->parseur->next;
	}
	exit(127);
}

void	ft_path_exec(char *str, t_shell *shell, char **args, int i)
{
	pid_t	pid;
	int		status;
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (memory_alloc_error(), (void)0);
	pid = fork();
	if (pid == 0 && i == 0)
		ft_path_exec_two(str, shell, args, var);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		shell->exit_status = wait_status_to_code(status);
	}
	if (pid < 0)
		perror("error");
}

void	dispatch_command_second(t_cmd *com_to_exec,
							t_shell *shell)
{
	if (ft_strncmp(com_to_exec->args[0], "pwd", 4) == 0)
		return (ft_pwd(shell->env, com_to_exec->args));
	else if (ft_strncmp(com_to_exec->args[0], "unset", 6) == 0)
		return (ft_unset(&shell->env, com_to_exec->args[1]));
	else if (ft_is_execute(com_to_exec->args[0], shell->env) == 2)
		return (ft_path_exec(com_to_exec->args[0],
				shell, com_to_exec->args, 0));
	else if (ft_is_execute(com_to_exec->args[0], shell->env) == 1)
		return (ft_exec(com_to_exec->args[0], com_to_exec->args, shell));
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(com_to_exec->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
	}
}
