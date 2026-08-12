/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/12 13:20:30 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(tab[i++]);
	free(tab);
}

t_env	*new_env_node(char *envp_entry)
{
	t_env	*new_var;
	char	**tmps;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	tmps = first_equal(envp_entry);
	new_var->value = NULL;
	new_var->name = ft_strdup(tmps[0]);
	if (tmps[1])
		new_var->value = ft_strdup(tmps[1]);
	new_var->next = NULL;
	free_chars(tmps);
	return (new_var);
}

void	set_env(t_env **var, char **envp)
{
	int		i;
	t_env	*cur;
	t_env	*new_var;

	cur = *var;
	i = 0;
	while (envp[i])
	{
		new_var = new_env_node(envp[i]);
		if (!new_var)
			return ;
		if (!*var)
			*var = new_var;
		else
			cur->next = new_var;
		new_var->equal = 1;
		cur = new_var;
		i++;
	}
}

t_env	*add_env_var(t_env **env, char *name, char *value)
{
	t_env	*node;
	t_env	*tail;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	node->next = NULL;
	node->equal = 1;
	if (!*env)
		return (*env = node, node);
	tail = *env;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
	return (node);
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
