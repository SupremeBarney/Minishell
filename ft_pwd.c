/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/28 18:32:22 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *pwd, char **args, int *exit_status)
{
	char	*ret;
	char	*s;
	char	cwd[4096];

	ret = NULL;
	s = NULL;
	*exit_status = 0;
	if (args[1] && args[1][1] && args[1][0] == '-')
	{
		s = ft_substr(args[1], 0, 2);
		ft_putstr_fd("bash: pwd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		free(s);
		*exit_status = 2;
		return ;
	}
	if (pwd)
		ret = get_env_value(pwd, "PWD");
	if (ret)
		printf("%s\n", ret);
	else if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
}
