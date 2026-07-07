/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_of_tokens(t_token *token)
{
	t_token	*cur;
	int		i;

	cur = token;
	i = 0;
	while (cur && cur->token_type != PIPE)
	{
		if (cur->token_type == WORD)
			i++;
		cur = cur->next;
	}
	return (i);
}

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

	if (!token)
		return (NULL);
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

int	valid_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp->token_type == PIPE)
		return (1);
	while (tmp)
	{
		if (((tmp->token_type >= PIPE && tmp->token_type <= REDIR_OUT_APPEND)
				&& !tmp->next)
			|| (tmp->token_type == PIPE && tmp->next->token_type == PIPE)
			|| ((tmp->token_type != WORD && tmp->token_type != PIPE)
				&& tmp->next->token_type != WORD))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
