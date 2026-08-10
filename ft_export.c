/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:06 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/09 13:51:04 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static int	ft_val_id_two(char *str)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	if (str[0] == '-')
	{
		printf("bash: export: '-%c': invalid option\n", str[1]);
		return (0);
	}
	while(str[i] && str[i] != '=')
	{
		if (str[i] == '@' || str[i] == '-' || str[i] == '.' || str[i] == '}' || str[i] == '{' || str[i] == '*' || str[i] == '#' || str[i] == '+')
			error++;
		if (str[i] == '!')
		{
			write (1, "bash: ", 6);
			while (str[i])
			{
				write (1, &str[i], 1);
				i++;
			}
			write (1, ": event not found\n", 18);
			return (0);
		}
		i++;
	}
	if (error >= 1)
	{
		printf("bash: export: '%s': not a valid identifier\n", str);
		return (0);	
	}
	return (1);
}

static int	ft_is_valid_identifier(char *str)
{
	int error;

	error = 0;
	if (str[0] == '\0')
	{
		printf("bash: export: `': not a valid identifier\n");
		return (0);
	}
	if (str[0] == '=')
		error++;
	if (str[0] == '%')
		error++;
	if (str[0] == '$' && str[1] == '?')
		error++;
	if (str[0] == '?')
		error++;
	if (str[0] >= '0' && str[0] <= '9')
		error++;
	if (error >= 1)
	{
		printf("bash: export: '%s': not a valid identifier\n", str);
		return (0);
	}
	return (ft_val_id_two(str));
}

int	ft_is_there_an_equal_or_not(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	if (str[i] == '=')
			return (1);
	return (0);
}

char	*before_equal(char *a)
{
	int		i;
	char	*ret;

	i = 0;
	while (a[i] && a[i] != '=')
		i++;
	ret = malloc(sizeof (char) * i + 1);
	i = 0;
	while(a[i] && a[i] != '=')
	{
		ret[i] = a[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*after_equal(char *a)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (a[i] && a[i] != '=')
		i++;
	if (a[i] != '=')
		return (ft_strdup(""));
	i++;
	while (a[i + j])
		j++;
	ret = malloc(sizeof (char) * j + 1);
	j = 0;
	while (a[i])
	{
		if (a[i] != ' ')
		{
			ret[j] = a[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

static void	ft_export_insert(t_env **env, t_env *new_node, char *first)
{
	t_env	*finder;
	t_env	*before;

	finder = *env;
	before = NULL;
	while (finder)
	{
		if (ft_strncmp(finder->name, first, ft_strlen(first) + 1) == 0)
		{
			finder->value = new_node->value;
			return ;
		}
		before = finder;
		finder = finder->next;
	}
	if (before)
		before->next = new_node;
	else
		*env = new_node;
}

void	ft_export(t_env **env, char **name)
{
	t_env	*new_node;
	char	*first;
	int		i;

	i = 1;
	if (!name[1])
	{
		if (*env)
			ft_env(*env);
		return ;
	}
	while (name[i])
	{
		if (ft_is_valid_identifier(name[i]) == 1)
		{
			first = before_equal(name[i]);
			new_node = malloc(sizeof(t_env));
			new_node->equal = ft_is_there_an_equal_or_not(name[i]);
			new_node->name = first;
			new_node->value = after_equal(name[i]);
			new_node->next = NULL;
			ft_export_insert(env, new_node, first);
		}
		i++;
	}
}
