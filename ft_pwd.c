/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/05/26 10:32:43 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void) //en argument, in nous faut au moin $PWD, mais je pense que pour chaque faction avoir la liste de variable d'environement serai bien
{
	char	*pwd;

	if (/*variable d'environement $PWD existe*/)
	{
		printf("%s", /*variable d'env $PWD *//);
		return ;
	}
	pwd = malloc(BUFFER_SIZE);
	if (!pwd) //si erreur d'alloc 
	{
		memory_alloc_error(); //si l'erreur d'alloc est ecrit
		return ; //il faut que le process d'exit ne return pas 0;
	}
	if (!getcwd(pwd, BUFFER_SIZE)) //si on est dans un fichier qui a ete effacer 
	{
		free (pwd);
		// il faut trouver un moyen d'afficher le dossier meme si il a ete effacer, utiliser $PWD?
		memory_alloc_error(); //l'erreur d'alloc est ecrit
		return ; //il faut que le process d'exit ne return pas 0;
	}
	printf("%s\n", pwd);
	free (pwd);
}

/*logic a faire: trouver un moyen d'utiliser $PWD au depart du lancement de programe (au lancement du programe minishell $PWD = getcwd, et ensuite update $PWD a chaque cd par le nouveau current directory), utiliser ce $PWD pour donner le pwd, et si l'utilisateur efface $PWD, utilised cwd en tant que dernier recour

int main (void)
{
	ft_pwd();
}*/
