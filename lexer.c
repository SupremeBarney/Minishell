/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/05/06 16:05:09 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_of_quotes(char *token)
{
	int	i;
	int	count_quote;
	int	flag;

	i = ((count_quote = flag = 0));
	while (token[i])
	{
		if (token[i] == '\'' && flag != 2)
		{
			flag = 1 - flag;
			count_quote++;
		}
		else if (token[i] == '"' && flag != 1)
		{
			flag = 2 - flag;
			count_quote++;
		}
		i++;
}
	return (count_quote);
}

char	*no_quotes(char *token)
{
	int		i;
	int		j;
	int		flag;
	char	*res;

	flag = ((i = j = 0));
	res = malloc(sizeof(char) * (ft_strlen(token) - nb_of_quotes(token) + 1));
	if (!res)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '\'' && flag != 2)
			flag = 1 - flag;
		else if (token[i] == '"' && flag != 1)
			flag = 2 - flag;
		else
			res[j++] = token[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	add_node(t_token **tokens, char *token)
{
	t_token	*cur;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->token = no_quotes(token);
	free(token);
	new_token->next = NULL;
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

void	handle_operator(char *str, t_token **tokens, int *i, int *start_token)
{
	if (*i != *start_token)
		add_node(tokens, ft_substr(str, *start_token, *i - *start_token));
	if (str[*i] == '|')
	{
		add_node(tokens, ft_strdup("|"));
		(*i)++;
		*start_token = *i;
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			add_node(tokens, ft_strdup("<<"));
			*i += 2;
			*start_token = *i;
		}
		else
		{
			add_node(tokens, ft_strdup("<"));
			(*i)++;
			*start_token = *i;
		}
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			add_node(tokens, ft_strdup(">>"));
			*i += 2;
			*start_token = *i;
		}
		else
		{
			add_node(tokens, ft_strdup(">"));
			(*i)++;
			*start_token = *i;
		}
	}
}

void	tokenisation(char *str, t_token **tokens)
{
	int	i;
	int	token_start;
	int	quote_flag;

	i = ((quote_flag = 0));
	while (str[i] == ' ')
		i++;
	token_start = i;
	while (str[i])
	{
		if (str[i] == '\'' && quote_flag != 2)
			quote_flag = 1 - quote_flag;
		else if (str[i] == '"' && quote_flag != 1)
			quote_flag = 2 - quote_flag;
		else if (str[i] == ' ' && quote_flag == 0)
		{
			add_node(tokens, ft_substr(str, token_start, i - token_start));
			while (str[i] == ' ')
					i++;
			token_start = i;
			continue;
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			handle_operator(str, tokens, &i, &token_start);
			while (str[i] == ' ')
				i++;
			token_start = i;
			continue;
		}
		i++;
	}
	if (i > token_start)
		add_node(tokens, ft_substr(str, token_start, i - token_start));
}

void	display_node(t_token *list)
{
	t_token	*node;

	node = list;
	while (node)
	{
		ft_printf("value : %s\n", node->token);
		node = node->next;
	}
}

int	valid_nb_quote(char *str)
{
	int	i;
	int	quote_flag;

	i = ((quote_flag = 0));
	while (str[i])
	{
		if (str[i] == '\'' && quote_flag != 2)
			quote_flag = 1 - quote_flag;
		else if (str[i] == '"' && quote_flag != 1)
			quote_flag = 2 - quote_flag;
		i++;
	}
	if (quote_flag)
		return (1);
	return (0);
}


int	main(void)
{
	t_token *tokens;

	tokens = NULL;
	if (valid_nb_quote("ls|grep foo"))
		exit(EXIT_FAILURE);
	tokenisation("ls|grep foo", &tokens); display_node(tokens);
}