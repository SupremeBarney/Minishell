/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/07/17 12:32:16 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_line(char *read_line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	cmd = NULL;
	if (valid_nb_quote(read_line))
		return (0);
	add_history(read_line);
	tokenisation(read_line, &tokens, *shell);
	if (!tokens)
		return (0);
	if (valid_syntax(tokens) == 1)
		return (free_tokens(tokens), ft_putstr_fd("Wrong Syntax\n", 2), 0);
	if (add_cmd_node(*shell, &cmd, tokens) == 1)
		return (free_tokens(tokens), 0);
	command_control(cmd, shell);
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
	shell.exit_status = 42;
	setup_signals();
	while (1)
	{
		g_signal = 0;
		read_line = readline("Barney$ ");
		if (!read_line)
			(free_env(&shell), exit(shell.exit_status));
		if (read_line[0])
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
