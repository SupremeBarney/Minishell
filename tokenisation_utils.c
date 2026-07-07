/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_left_redir(char *str, t_token **tokens, int *i, t_shell shell)
{
	if (str[*i + 1] == '<')
	{
		add_node(tokens, ft_strdup("<<"), shell);
		*i += 2;
	}
	else
	{
		add_node(tokens, ft_strdup("<"), shell);
		(*i)++;
	}
}

void	handle_right_redir(char *str, t_token **tokens, int *i, t_shell shell)
{
	if (str[*i + 1] == '>')
	{
		add_node(tokens, ft_strdup(">>"), shell);
		*i += 2;
	}
	else
	{
		add_node(tokens, ft_strdup(">"), shell);
		(*i)++;
	}
}

void	tok_space(char *str, t_token **tokens, t_parse *p, t_shell shell)
{
	char	*tmp;

	tmp = ft_substr(str, p->token_start, p->i - p->token_start);
	if (tmp)
		add_node(tokens, tmp, shell);
	while (str[p->i] == ' ')
		p->i++;
	p->token_start = p->i;
}

void	tok_operator(char *str, t_token **tokens, t_parse *p, t_shell shell)
{
	char	*tmp;

	if (p->i > p->token_start)
	{
		tmp = ft_substr(str, p->token_start, p->i - p->token_start);
		if (tmp)
			add_node(tokens, tmp, shell);
	}
	handle_operator(str, tokens, &p->i, shell);
	while (str[p->i] == ' ')
		p->i++;
	p->token_start = p->i;
}
