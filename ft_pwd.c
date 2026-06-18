/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/18 12:12:23 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *pwd) //en argument, in nous faut au moin $PWD, mais je pense que pour chaque faction avoir la liste de variable d'environement serai bien
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (!pwd)
		return ;
	else
	{
		ret = get_env_value(pwd, "PWD");
		if (ret)
			printf("%s", ret);
	}
}

/*logic a faire: trouver un moyen d'utiliser $PWD au depart du lancement de programe (au lancement du programe minishell $PWD = getcwd, et ensuite update $PWD a chaque cd par le nouveau current directory), utiliser ce $PWD pour donner le pwd, et si l'utilisateur efface $PWD, utilised cwd en tant que dernier recour

int main (void)
{
	ft_pwd();
}*/
