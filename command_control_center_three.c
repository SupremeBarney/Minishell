/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center_three.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 17:21:52 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_execute(char *str, t_env *first_env)
{
	t_env	*parseur;

	parseur = first_env;
	while (parseur)
	{
		if (ft_strncmp(parseur->name, "PATH", 5) == 0
			&& parseur->value && ft_search_path(parseur->value, str))
			return (2);
		parseur = parseur->next;
	}
	if ((str[0] == '.' && str[1] == '/') || (str[0] == '/'))
		return (1);
	return (0);
}

void	pid_check(pid_t pid, t_shell *shell)
{
	if (pid > 0)
		shell->exit_status = wait_child(pid);
	if (pid < 0)
		perror("error");
}
