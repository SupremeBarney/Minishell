/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/05/22 13:35:46 by alexfran         ###   ########.fr       */
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

void	add_cmd_node(t_cmd **cmd, t_token *tokens)
{
	int		i;
	t_token	*cur_token;
	t_cmd	*cur_cmd;

	i = 0;
	cur_token = tokens;
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!(*cmd))
		return ;
	cur_cmd = *cmd;
	cur_cmd->args = malloc(sizeof(char *) * (nb_of_tokens(tokens) + 1));
	if (!cur_cmd->args)
		return ;
	while (cur_token)
	{
		if (cur_token->token_type == WORD)
		{
			cur_cmd->args[i++] = ft_strdup(cur_token->token);
			if (!cur_token->next || cur_token->next->token_type != WORD)
				cur_cmd->args[i] = NULL;
		}
		else if (cur_token->token_type == PIPE)
		{
			i = 0;
			cur_token = cur_token->next;
			cur_cmd->next = ft_calloc(1, sizeof(t_cmd));
			if (!cur_cmd->next)
				return ;
			cur_cmd = cur_cmd->next;
			cur_cmd->args = malloc(sizeof(char *)
					* (nb_of_tokens(cur_token) + 1));
			if (!cur_cmd->args)
				return ;
			continue ;
		}
		else if (cur_token->token_type == REDIR_IN)
		{
			cur_token = cur_token->next;
			cur_cmd->input = ft_strdup(cur_token->token);
		}
		else if (cur_token->token_type == HEREDOC)
		{
			cur_token = cur_token->next;
			cur_cmd->heredoc = ft_strdup(cur_token->token);
		}
		else if (cur_token->token_type == REDIR_OUT)
		{
			cur_token = cur_token->next;
			cur_cmd->output = ft_strdup(cur_token->token);
		}
		else if (cur_token->token_type == REDIR_OUT_APPEND)
		{
			cur_token = cur_token->next;
			cur_cmd->output_append = ft_strdup(cur_token->token);
		}
		cur_token = cur_token->next;
	}
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

t_token_type	which_type(char *token)
{
	int				i;

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

void	add_node(t_token **tokens, char *token)
{
	t_token	*cur;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->token = no_quotes(token);
	new_token->token_type = which_type(token);
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
		ft_printf("type : %d\n", node->token_type);
		node = node->next;
	}
}

void	display_cmd(t_cmd *cmd)
{
	t_cmd	*node;
	int		i;

	node = cmd;
	while (node)
	{
		i = 0;
		while (node->args[i])
			ft_printf("args : %s\n", node->args[i++]);
		ft_printf("input : %s\noutput : %s\nheredoc : %s\noutput_append : %s\n\n", node->input, node->output, node->heredoc, node->output_append);
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
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	if (valid_nb_quote("ls|grep foo"))
		exit(EXIT_FAILURE);
	tokenisation("ls | grep foo < input.txt > output.txt", &tokens);
	display_node(tokens);
	add_cmd_node(&cmd, tokens);
	display_cmd(cmd);
}
