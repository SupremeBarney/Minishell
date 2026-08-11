/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:26:13 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/31 15:34:59 by nipichon         ###   ########.fr       */
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

static long long	ft_exit_atoll(char *str, int *overflow)
{
	unsigned long long	res;
	unsigned long long	limit;
	int					neg;
	int					i;

	i = 0;
	neg = 1;
	res = 0;
	*overflow = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	limit = 9223372036854775807ULL + (neg == -1);
	while (str[i])
	{
		if (res > (limit - (str[i] - '0')) / 10)
			*overflow = 1;
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (neg == -1)
		res = -res;
	return ((long long)res);
}

static int	ft_exit_code(char *arg, int prev_status)
{
	long long	code;
	int			overflow;

	if (!arg)
		return (prev_status);
	if (!ft_is_exitable_char_check(arg))
	{
		printf("bash: exit: %s: numeric argument required\n", arg);
		return (2);
	}
	code = ft_exit_atoll(arg, &overflow);
	if (overflow)
	{
		printf("bash: exit: %s: numeric argument required\n", arg);
		return (2);
	}
	return ((unsigned char)code);
}

void	ft_exit(int exit_status, t_token *tokens, t_cmd *cmd, t_shell shell)
{
	int	args_num;

	args_num = ft_check_num_args(cmd->args);
	if (args_num > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	exit_status = ft_exit_code(cmd->args[1], exit_status);
	free_tokens(tokens);
	free_cmd(cmd);
	free_env(&shell);
	clear_history();
	exit(exit_status);
}


