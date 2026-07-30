/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/07/30 15:56:52 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	slash_parser(char *read_line)
{
	if (read_line[0] == '/')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(read_line, 2);
		ft_putstr_fd("\": Is a directory\n", 2);
		return (1);
	}
	return (0);
}

int	pipe_with_space(char *read_line)
{
	if (read_line[0] == '|' && read_line[1] == ' ')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

int	ampersand_parser(char *read_line)
{
	if (read_line[0] == '&')
	{
		if (read_line[1] == '&')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
			return (1);
		}
		ft_putstr_fd("bash: syntax error near unexpected token `&'\n", 2);
		return (1);
	}
	return (0);
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
