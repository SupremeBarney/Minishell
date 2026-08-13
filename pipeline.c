/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:52:19 by alexfran          #+#    #+#             */
/*   Updated: 2026/07/30 17:14:03 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_cmds(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

void	wait_pipeline(pid_t last_pid, t_shell *shell)
{
	shell->exit_status = wait_child(last_pid);
	signal(SIGINT, SIG_IGN);
	while (waitpid(-1, NULL, 0) > 0)
		;
	setup_signals();
}

void	pipeline_child(t_cmd *cur, t_shell *shell, t_token *tokens, t_pipe *pfd)
{
	reset_child_signals();
	if (pfd->prev_fd != -1)
		(dup2(pfd->prev_fd, STDIN_FILENO), close(pfd->prev_fd));
	if (cur->next)
		(close(pfd->fd[0]), dup2(pfd->fd[1], STDOUT_FILENO),
			close(pfd->fd[1]));
	if (apply_redirections(cur) == -1)
		exit(1);
	dispatch_command(cur, shell, tokens);
	exit(shell->exit_status);
}

void	pipeline_parent(t_cmd *cur, t_pipe *pfd)
{
	if (pfd->prev_fd != -1)
		close(pfd->prev_fd);
	if (cur->next)
		(close(pfd->fd[1]), pfd->prev_fd = pfd->fd[0]);
}

void	execute_pipeline(t_cmd *cmd, t_shell *shell, t_token *tokens)
{
	t_pipe	pfd;
	pid_t	pid;
	pid_t	last_pid;
	t_cmd	*cur;

	pfd.prev_fd = -1;
	cur = cmd;
	while (cur)
	{
		if (cur->next)
			pipe(pfd.fd);
		pid = fork();
		if (pid == 0)
			pipeline_child(cur, shell, tokens, &pfd);
		pipeline_parent(cur, &pfd);
		if (!cur->next)
			last_pid = pid;
		cur = cur->next;
	}
	wait_pipeline(last_pid, shell);
}
