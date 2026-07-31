/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:26:13 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/31 15:30:30 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_check_num_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static	int	ft_is_exitable_char_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(int exit_status, t_token *tokens, t_cmd *cmd, t_shell shell)
{
	int	args_num;

	args_num = ft_check_num_args(cmd->args);
	if (ft_is_exitable_char_check(cmd->args[1]) == 0)
	{
		printf("bash: exit: \"%s\": numeric argument required\n", cmd->args[1]);
		return ;
	}
	if (args_num > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	free_tokens(tokens);
	free_cmd(cmd);
	free_env(&shell);
	clear_history();
	exit(exit_status);
}


