/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/12 14:44:37 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_pipe_all(int fd)
{
	char	buf[1024];
	char	*res;
	int		n;

	res = ft_strdup("");
	n = read(fd, buf, 1023);
	while (n > 0)
	{
		buf[n] = 0;
		res = strjoin_free(res, buf);
		n = read(fd, buf, 1023);
	}
	return (res);
}

void	heredoc_write(char *expanse, char *tmp, int *pipe_fd)
{
	free(tmp);
	write(pipe_fd[1], expanse, ft_strlen(expanse));
	write(pipe_fd[1], "\n", 1);
	free(expanse);
}

void	heredoc_child(int *pipe_fd, char *delimiter, t_shell shell, int expand)
{
	char	*tmp;
	char	*expanse;

	signal(SIGINT, SIG_DFL);
	close(pipe_fd[0]);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (!ft_strncmp(delimiter, tmp, ft_strlen(delimiter) + 1))
		{
			free(tmp);
			break ;
		}
		if (expand)
			expanse = heredoc_expansion(tmp, shell);
		else
			expanse = ft_strdup(tmp);
		heredoc_write(expanse, tmp, pipe_fd);
	}
	close(pipe_fd[1]);
	exit(0);
}

char	*read_heredoc(char *delimiter, t_shell shell, int expand)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	*res;

	if (pipe(pipe_fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == 0)
		heredoc_child(pipe_fd, delimiter, shell, expand);
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	res = read_pipe_all(pipe_fd[0]);
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (free(res), write(1, "\n", 1), NULL);
	return (res);
}

int	apply_heredoc(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (!cmd->heredoc)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (-1);
	write(pipe_fd[1], cmd->heredoc, ft_strlen(cmd->heredoc));
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}
