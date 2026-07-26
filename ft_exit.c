/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:26:13 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/25 15:49:45 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int exit_status, t_token *tokens, t_cmd *cmd, t_shell shell)
{
	free_tokens(tokens);
	free_cmd(cmd);
	free_env(&shell);
	free(shell.read_line);
	clear_history();
	exit(exit_status);
}
