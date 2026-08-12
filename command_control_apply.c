/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_apply.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 14:30:33 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_input(t_cmd *cmd)
{
	int	fd;

	if (cmd->input)
	{
		fd = open(cmd->input, O_RDONLY);
		if (fd == -1)
			return (ft_putstr_fd("bash: ", 2), perror(cmd->input), -1);
		(dup2(fd, STDIN_FILENO), close(fd));
	}
	if (apply_heredoc(cmd) == -1)
		return (-1);
	return (0);
}

int	apply_output(t_cmd *cmd)
{
	int	fd;

	if (cmd->output)
	{
		fd = open(cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd == -1)
			return (ft_putstr_fd("bash: ", 2), perror(cmd->output), -1);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	if (cmd->output_append)
	{
		fd = open(cmd->output_append, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (fd == -1)
			return (ft_putstr_fd("bash: ", 2), perror(cmd->output_append), -1);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	return (0);
}
