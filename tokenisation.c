/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	which_type(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '|')
		return (PIPE);
	else if (token[i] == '<')
	{
		if (token[i + 1] == '<')
			return (HEREDOC);
		return (REDIR_IN);
	}
	else if (token[i] == '>')
	{
		if (token[i + 1] == '>')
			return (REDIR_OUT_APPEND);
		return (REDIR_OUT);
	}
	else
		return (WORD);
}

void	add_node(t_token **tokens, char *token, t_shell shell)
{
	t_token	*cur;
	t_token	*new_token;

	if (!token)
		return ;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->token_type = which_type(token);
	new_token->had_quotes = (nb_of_quotes(token) > 0);
	if (new_token->token_type == WORD)
		new_token->token = expansion(token, shell);
	else
		new_token->token = ft_strdup(token);
	new_token->next = NULL;
	free(token);
	if (!*tokens)
		*tokens = new_token;
	else
	{
		cur = *tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
	}
}

void	handle_operator(char *str, t_token **tokens, int *i, t_shell shell)
{
	if (str[*i] == '|')
	{
		add_node(tokens, ft_strdup("|"), shell);
		(*i)++;
	}
	else if (str[*i] == '<')
		handle_left_redir(str, tokens, i, shell);
	else if (str[*i] == '>')
		handle_right_redir(str, tokens, i, shell);
}

void	tokenise_loop(char *str, t_token **tokens, t_parse *p, t_shell shell)
{
	while (str[p->i])
	{
		if (str[p->i] == '\'' && p->quote_flag != 2)
			p->quote_flag = 1 - p->quote_flag;
		else if (str[p->i] == '"' && p->quote_flag != 1)
			p->quote_flag = 2 - p->quote_flag;
		else if (str[p->i] == ' ' && p->quote_flag == 0)
		{
			tok_space(str, tokens, p, shell);
			continue ;
		}
		else if (str[p->i] == '|' || str[p->i] == '<' || str[p->i] == '>')
		{
			tok_operator(str, tokens, p, shell);
			continue ;
		}
		p->i++;
	}
}

void	tokenisation(char *str, t_token **tokens, t_shell shell)
{
	t_parse	p;
	char	*tmp;

	p.i = 0;
	p.quote_flag = 0;
	while (str[p.i] == ' ')
		p.i++;
	p.token_start = p.i;
	tokenise_loop(str, tokens, &p, shell);
	if (p.i > p.token_start)
	{
		tmp = ft_substr(str, p.token_start, p.i - p.token_start);
		if (tmp)
			add_node(tokens, tmp, shell);
	}
}
