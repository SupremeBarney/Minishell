/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 16:25:52 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char *str, char **args, t_shell *shell)
{
	t_exec_info	info;
	t_env		*parseur;

	if (!shell->env)
		return ;
	parseur = shell->env;
	info.pwd = NULL;
	while (parseur)
	{
		if (ft_strncmp("PWD", parseur->name, 4) == 0)
			info.pwd = ft_strdup(parseur->value);
		parseur = parseur->next;
	}
	info.envp = ft_envp(shell->env);
	info.shell = shell;
	ft_which_exec(str, args, &info);
	free(info.pwd);
	free_chars(info.envp);
}

void	ft_which_exec(char *str, char **args, t_exec_info *info)
{
	if (!str)
		return ;
	else if (ft_strncmp(str, "./", 2) == 0)
	{
		ft_exec_relative_path(str, args, info);
	}
	else if (str[0] == '/')
	{
		ft_exec_true_path(str, args, info);
		return ;
	}
}

int	ft_is_dir(char *str)
{
	struct stat	st;

	if (stat(str, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	ft_exec_child_error(char *str)
{
	int	err;

	err = errno;
	ft_putstr_fd("bash: ", 2);
	perror(str);
	if (err == EACCES)
		exit(126);
	exit(127);
}

void	ft_exec_true_path(char *str, char **args, t_exec_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		reset_child_signals();
		if (ft_is_dir(str))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit(126);
		}
		if (execve(str, args, info->envp) == -1)
			ft_exec_child_error(str);
	}
	if (pid > 0)
		info->shell->exit_status = wait_child(pid);
	if (pid < 0)
		perror("Eror");
}
