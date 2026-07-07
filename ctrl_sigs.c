/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_sigs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:27:24 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/15 16:41:49 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//il faut qu'il soit appeler avec des sigactions
void	ctrl_c()
{
	break;
}

void	ctrl_d()
{
	ft_exit();
}

void	ctrl_sep()
{
	return ;
}

void	handle_sig(int sig)
{
	if (sig == SIGINT) //CTRL+C
	{
		ctr_c();
		return ;
	}
	if (sig == SIGQUIT) //CTRL+D and CTRL+\ ??? to check on this one, I think a simple do not care about CTRL+D since it'll close the termianl anyway ;ight work? To check
	{
		ctrl_d();
		return;
	}
}