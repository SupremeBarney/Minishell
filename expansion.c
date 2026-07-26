/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/07/26 15:53:18 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*handle_dollar(char *str, int *i, t_shell shell, int flag)
{
	int		j;
	char	*var;
	char	*value;

	(*i)++;
	j = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell.exit_status));
	}
	else if (ft_isdigit(str[*i]))
		return ((*i)++, ft_strdup(""));
	else if (flag == 0 && (str[*i] == '\'' || str[*i] == '"'))
		return (ft_strdup(""));
	else if (!ft_isalpha(str[*i]) && str[*i] != '?' && str[*i] != '_')
		return (ft_strdup("$"));
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, j, *i - j);
	value = get_env_value(shell.env, var);
	free(var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

int	handle_quote_flag(char c, int *flag)
{
	if (c == '\'' && *flag != 2)
		return (*flag = 1 - *flag, 1);
	if (c == '"' && *flag != 1)
		return (*flag = 2 - *flag, 1);
	return (0);
}

void	process_char(char *str, int *state, char **res, t_shell shell)
{
	char	*tmp_dollar;
	char	tmp[2];

	tmp[1] = 0;
	if (handle_quote_flag(str[state[0]], &state[1]))
		state[0]++;
	else if (str[state[0]] == '\\' && str[state[0] + 1] == '$'
		&& state[1] != 1)
	{
		tmp[0] = '$';
		*res = strjoin_free(*res, tmp);
		state[0] += 2;
	}
	else if (str[state[0]] == '$' && state[1] != 1)
	{
		tmp_dollar = handle_dollar(str, &state[0], shell, state[1]);
		*res = strjoin_free(*res, tmp_dollar);
		free(tmp_dollar);
	}
	else
	{
		tmp[0] = str[state[0]++];
		*res = strjoin_free(*res, tmp);
	}
}

char	*expansion(char *str, t_shell shell)
{
	int		state[2];
	char	*res;

	state[0] = 0;
	state[1] = 0;
	res = ft_strdup("");
	while (str[state[0]])
		process_char(str, state, &res, shell);
	return (res);
}
