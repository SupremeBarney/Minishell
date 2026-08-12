/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/12 12:33:28 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_printf("input : %s\noutput : %s\n", node->input, node->output);
		ft_printf("heredoc : %s\noutput_append : %s\n\n",
			node->heredoc, node->output_append);
		node = node->next;
	}
}

void	display_env(t_env *var)
{
	t_env	*cur;

	if (!var)
		return ;
	cur = var;
	while (cur)
	{
		printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
}
