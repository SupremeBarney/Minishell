/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 14:48:03 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *pwd, char **args)
{
	char	*ret;
	char	*s;
	char	cwd[4096];

	ret = ((s = NULL));
	if (args[1] && args[1][1] && args[1][0] == '-')
	{
		s = ft_substr(args[1], 0, 2);
		ft_putstr_fd("bash: pwd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		free(s);
		return ;
	}
	if (pwd)
		ret = get_env_value(pwd, "PWD");
	if (ret)
		printf("%s\n", ret);
	else if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
}
