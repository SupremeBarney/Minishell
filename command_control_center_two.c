/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center_two.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 17:21:43 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_path_has_exec(char *dir, char *str)
{
	struct stat	st;
	char		*tmp;
	char		*full;
	int			ok;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, str);
	free(tmp);
	ok = (stat(full, &st) == 0 && S_ISREG(st.st_mode)
			&& access(full, X_OK) == 0);
	free(full);
	return (ok);
}

int	ft_search_path(char *value, char *str)
{
	char	**path;
	int		i;

	path = ft_split(value, ':');
	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		if (ft_path_has_exec(path[i], str))
			return (free_chars(path), 1);
		i++;
	}
	return (free_chars(path), 0);
}

void	path_exec_two(char **path, char *str, char **args, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(tmp, str);
		if (execve(path[i], args, envp) != -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	ft_path_exec(char *str, t_shell *shell, char **args, int i)
{
	t_env	*parseur;
	char	**path;
	char	**envp;
	pid_t	pid;

	pid = fork();
	if (pid == 0 && i == 0)
	{
		reset_child_signals();
		parseur = shell->env;
		i = 0;
		while (parseur)
		{
			if (ft_strncmp(parseur->name, "PATH", 5) == 0)
			{
				envp = ft_envp(shell->env);
				path = ft_split (parseur->value, ':');
				path_exec_two(path, str, args, envp);
			}
			parseur = parseur->next;
		}
		exit(127);
	}
	pid_check(pid, shell);
}
