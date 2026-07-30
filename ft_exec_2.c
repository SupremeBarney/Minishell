/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:12:56 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/30 18:55:40 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_find_pwd(t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, "PWD", 4) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	wait_status_to_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
