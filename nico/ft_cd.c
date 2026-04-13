/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/13 13:22:10 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *str, t_pathfile *current_file, t_all_files *files)
{
	int			i;
	t_pathfile	*tmp;

	if (!current_file || !files)
		return (ft_exit());
	tmp = files->first_file;
	while (tmp && tmp->next_file)
	{
		i = 0;
		if (str == tmp->absolute_pathfile)
		{
			current_file = tmp;
			return ;
		}
		while (tmp->relative_pathfiles[i])
		{
			if (str == tmp->relative_pathfiles[i])
			{
				current_file = tmp;
				return ;
			}
		}
		tmp = tmp->next_file;
	}
}
