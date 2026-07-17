/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/17 12:33:43 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *pwd) //en argument, in nous faut au moin $PWD, mais je pense que pour chaque faction avoir la liste de variable d'environement serai bien
{
	char	*ret;

	ret = NULL;
	if (!pwd)
		return ;
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
