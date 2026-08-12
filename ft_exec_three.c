/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 15:11:59 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_relative_path(char *str, char **args, t_exec_info *info)
{
	char	*ret;
	char	*tmp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		tmp = ft_strjoin(info->pwd, "/");
		str = ft_enlever_str(str);
		ret = ft_strjoin(tmp, str);
		free (tmp);
		if (execve(ret, args, info->envp) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		info->shell->exit_status = wait_status_to_code(status);
	}
	if (pid < 0)
		perror("EROROR");
}
