/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/12 14:44:24 by alexfran         ###   ########.fr       */
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

char	*handle_dollar(char *str, int *i, t_shell shell)
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

char	*expansion(char *str, t_shell shell)
{
	int		i;
	int		flag;
	char	*res;
	char	*tmp_dollar;
	char	tmp[2];

	i = ((flag = tmp[1] = 0));
	res = ft_strdup("");
	while (str[i])
	{
		if (handle_quote_flag(str[i], &flag))
			i++;
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
