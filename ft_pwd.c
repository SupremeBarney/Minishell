/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/28 18:32:22 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *pwd, char **args) //en argument, in nous faut au moin $PWD, mais je pense que pour chaque faction avoir la liste de variable d'environement serai bien
{
	char	*ret;
	char	*s;

	ret = ((s = NULL));
	if (!pwd)
		return ;
	if (args[1] && args[1][1] && args[1][0] == '-')
	{
		s = ft_substr(args[1], 0, 2);
		ft_putstr_fd("bash: pwd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		free(s);
		return ;
	}
	else
	{
		ret = get_env_value(pwd, "PWD");
		if (ret)
			printf("%s\n", ret);
	}
}

/*logic a faire: trouver un moyen d'utiliser $PWD au depart du lancement de programe (au lancement du programe minishell $PWD = getcwd, et ensuite update $PWD a chaque cd par le nouveau current directory), utiliser ce $PWD pour donner le pwd, et si l'utilisateur efface $PWD, utilised cwd en tant que dernier recour

int main (void)
{
	ft_pwd();
}*/
