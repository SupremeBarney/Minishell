/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/24 18:55:35 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expansion(char *str, t_shell shell)
{
	int		i;
	int		flag;
	char	*res;
	char	*tmp_dollar;
	char	tmp[2];

	i = ((flag = 0));
	res = ft_strdup("");
	tmp[1] = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp_dollar = handle_dollar(str, &i, shell, flag);
			res = strjoin_free(res, tmp_dollar);
			free(tmp_dollar);
		}
		else
		{
			tmp[0] = str[i++];
			res = strjoin_free(res, tmp);
		}
	}
	return (res);
}

static char	*heredoc_line(char *tmp, t_shell shell, int expand)
{
	if (expand)
		return (heredoc_expansion(tmp, shell));
	return (ft_strdup(tmp));
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
		expanse = heredoc_line(tmp, shell, expand);
		free(tmp);
		write(pipe_fd[1], expanse, ft_strlen(expanse));
		write(pipe_fd[1], "\n", 1);
		free(expanse);
	}
	close(pipe_fd[1]);
	exit(0);
}

char	*read_heredoc(char *delimiter, t_shell *shell, int expand)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	*res;

	if (pipe(pipe_fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == 0)
		heredoc_child(pipe_fd, delimiter, *shell, expand);
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	res = read_pipe_all(pipe_fd[0]);
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		return (free(res), write(0, "\n", 1), NULL);
	}
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
