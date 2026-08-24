/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 19:09:00 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/24 19:09:00 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_quote_status(int status, char *res, t_shell *shell)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		return (free(res), write(1, "\n", 1), NULL);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (free(res), NULL);
	return (res);
}
