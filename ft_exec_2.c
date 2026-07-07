/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:12:56 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/07 09:48:15 by nipichon         ###   ########.fr       */
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
