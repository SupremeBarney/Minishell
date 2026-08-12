/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/12 14:23:38 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_child(int *pipe_fd, char *read_line)
{
	char	*tmp;
	int		state;

	signal(SIGINT, SIG_DFL);
	close(pipe_fd[0]);
	state = quote_state(read_line);
	while (state != 0)
	{
		tmp = readline("> ");
		quotes_error(tmp, state);
		if (!tmp)
			exit(1);
		read_line = strjoin_free(read_line, "\n");
		read_line = strjoin_free(read_line, tmp);
		free(tmp);
		state = quote_state(read_line);
	}
	write(pipe_fd[1], read_line, ft_strlen(read_line));
	close(pipe_fd[1]);
	exit(0);
}

char	*complete_quotes(char *read_line)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	*res;

	if (quote_state(read_line) == 0)
		return (read_line);
	if (pipe(pipe_fd) == -1)
		return (read_line);
	pid = fork();
	if (pid == 0)
		quotes_child(pipe_fd, read_line);
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	res = read_pipe_all(pipe_fd[0]);
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	setup_signals();
	free(read_line);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (free(res), NULL);
	return (res);
}

int	process_line(char *read_line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	cmd = NULL;
	if (slash_parser(read_line) || pipe_with_space(read_line)
		|| ampersand_parser(read_line))
		return (add_history(read_line), 0);
	add_history(read_line);
	tokenisation(read_line, &tokens, *shell);
	if (!tokens)
		return (0);
	if (valid_syntax(tokens) == 1)
		return (free_tokens(tokens), 0);
	if (add_cmd_node(*shell, &cmd, tokens) == 1)
		return (free_tokens(tokens), 0);
	if (nb_cmds(cmd) > 1)
		execute_pipeline(cmd, shell, tokens);
	else
		command_control(cmd, shell, tokens);
	free_tokens(tokens);
	free_cmd(cmd);
	return (0);
}

void	main_loop(char **envp)
{
	t_shell	shell;
	char	*read_line;

	shell.env = NULL;
	set_env(&shell.env, envp);
	shell.exit_status = 0;
	setup_signals();
	while (1)
	{
		g_signal = 0;
		read_line = readline("Barney$ ");
		if (!read_line)
			(free_env(&shell), exit(shell.exit_status));
		if (read_line[0])
			read_line = complete_quotes(read_line);
		if (read_line && read_line[0])
			process_line(read_line, &shell);
		free(read_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	main_loop(envp);
}
