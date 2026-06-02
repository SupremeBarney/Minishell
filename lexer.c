/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/02 15:37:39 by alexfran         ###   ########.fr       */
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

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->heredoc = NULL;
	cmd->output_append = NULL;
	cmd->next = NULL;
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
	init_cmd(*cmd);
	cur_cmd = *cmd;
	cur_cmd->args = malloc(sizeof(char *) * (nb_of_tokens(tokens) + 1));
	if (!cur_cmd->args)
		return ;
	while (cur_token)
	{
		if (cur_token->token_type == WORD)
			cur_cmd->args[i++] = ft_strdup(cur_token->token);
		else if (cur_token->token_type == PIPE)
		{
			cur_cmd->args[i] = NULL;
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
	cur_cmd->args[i] = NULL;
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

void	add_node(t_token **tokens, char *token)
{
	t_token	*cur;
	t_token	*new_token;

	if (!token)
		return ;
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
	char	*tmp;

	if (*i != *start_token)
	{
		tmp = ft_substr(str, (unsigned int)*start_token, i - start_token);
		if (tmp)
			add_node(tokens, tmp);
	}
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
	int		i;
	int		token_start;
	int		quote_flag;
	char	*tmp;

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
			tmp = ft_substr(str, token_start, i - token_start);
			if (tmp)
				add_node(tokens, tmp);
			while (str[i] == ' ')
				i++;
			token_start = i;
			continue ;
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			handle_operator(str, tokens, &i, &token_start);
			while (str[i] == ' ')
				i++;
			token_start = i;
			continue ;
		}
		i++;
	}
	if (i > token_start)
	{
		tmp = ft_substr(str, token_start, i - token_start);
		if (tmp)
			add_node(tokens, tmp);
	}
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

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd)
	{
		i = 0;
		tmp = cmd->next;
		if (cmd->args)
		{
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->input)
			free(cmd->input);
		if (cmd->heredoc)
			free(cmd->heredoc);
		if (cmd->output)
			free(cmd->output);
		if (cmd->output_append)
			free(cmd->output_append);
		free(cmd);
		cmd = tmp;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->token);
		free(tokens);
		tokens = tmp;
	}
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


char	**first_equal(char *str)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * 3);
	while (str[i] != '=' && str[i])
		i++;
	res[0] = ft_substr(str, 0, i);
	if (str[i] == '=')
	{
		j = i + 1;
		while (str[i])
			i++;
		res[1] = ft_substr(str, j, i - j);
		res[2] = 0;
	}
	else
	{
		res[1] = NULL;
		res[2] = 0;
	}
	return (res);
}

void	free_chars(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	free (tab);
}

void	set_env(t_env **var, char **envp)
{
	int		i;
	t_env	*cur;
	t_env	*new_var;
	char	**tmps;

	cur = *var;
	i = 0;
	while (envp[i])
	{
		new_var = malloc(sizeof(t_env));
		if (!new_var)
			return ;
		tmps = first_equal(envp[i]);
		new_var->value = NULL;
		new_var->name = ft_strdup(tmps[0]);
		if (tmps[1])
			new_var->value = ft_strdup(tmps[1]);
		new_var->next = NULL;
		if (!*var)
			*var = new_var;
		else
			cur->next = new_var;
		cur = new_var;
		i++;
		free_chars (tmps);
	}
}

void	display_env(t_env *var)
{
	t_env	*cur;

	cur = var;
	while (cur)
	{
		printf("%s : %s\n", cur->name, cur->value);
		cur = cur->next;
	}
}

char	*get_env_value(t_env *env, char *name)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->name, name, ft_strlen(name) + 1) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free (s1);
	return (res);
}
char	*handle_dollar(char *str, int *i, t_shell *shell)
{
	int		j;
	char	*var;
	char	*value;

	(*i)++;
	j = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, j, *i - j);
	value = get_env_value(shell->env, var);
	free(var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char    *expansion(char *str, t_shell *shell)
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
		if (str[i] == '\'' && flag != 2)
		{
			flag = 1 - flag;
			i++;
		}
		else if (str[i] == '\"' && flag != 1)
		{
			flag = 2 - flag;
			i++;
		}
		else if (str[i] == '$' && flag != 1)
		{
			tmp_dollar = handle_dollar(str, &i, shell);
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

void	main_loop(char **envp)
{
	t_shell	shell;
	t_token	*tokens;
	t_cmd	*cmd;
	char	*read_line;

	shell.env = NULL;
	set_env(&shell.env, envp);
	shell.exit_status = 0;
	while (1)
	{
		tokens = NULL;
		cmd = NULL;
		//display_env(var);
		read_line = readline("Barney$ ");
		if (!read_line || valid_nb_quote(read_line))
			exit(EXIT_FAILURE);
		if (!read_line[0])
		{
			free (read_line);
			continue ;
		}
		add_history(read_line);
		tokenisation(read_line, &tokens);
		if (!tokens)
		{
			free (read_line);
			continue ;
		}
		if (valid_syntax(tokens) == 1)
		{
			free (read_line);
			free_tokens(tokens);
			ft_putstr_fd("Wrong Syntax\n", 2);
			continue ;
		}
		display_node(tokens);
		add_cmd_node(&cmd, tokens);
		display_cmd(cmd);
		free_tokens(tokens);
		free_cmd(cmd);
		free (read_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	main_loop(envp);
}
