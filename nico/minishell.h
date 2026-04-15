/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:31:14 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/15 16:35:02 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>


typedef struct s_environment_variables{
	char					*variable_name;
	char					*variable_value;
	t_environment_variable	*next;
}	t_environment_variable;

typedef struct s_all_env_var{
	int						total_num_env_var;
	t_environment_variable	*first_env_var;
}	t_all_env_var;

typedef struct s_pathfile{
	char		*absolute_pathfile;
	char		**relative_pathfiles; //the ones you can do with a simple cd
	t_pathfile	*next_file; //classic next_list, but just so you know, with this method, it won't check them in clean order per directory, but by order of creation.
}	t_pathfile;

typedef struct s_all_files{
	t_pathfile	*first_file; //   so ~/
	int			all_files_size;
	t_pathfile	*current_file;
}	t_all_files;

typedef struct s_args{
	char	**val;
	int		**is_special; //check to see if the char's value at argument[argument number X][char Y of that argument] is one of the expections like "'/& and others, 1 for true, rest is 0, could also make it a bool? 
} t_args;

typedef struct s_current_command{
	char	*command;
	t_args	*args;
	char	*option;
	int		num_of_args;
}	t_current_command;

typedef struct s_history{
	char		*command;
	int			index;
	t_history	*next;
}	t_history;

void	ft_exit(void);
void	ft_echo(char *str);
void	ft_echo_n(char *str);
void	ft_cd(char *str, t_pathfile *current_file, t_all_files *files);
void	ft_pwd(t_pathfile *current_file);
void	ft_unset(char var_to_unset, t_all_env_var *dir_of_vars);
void	ft_nothing_to_unset(void);
void	ft_env(char *name, char *value, t_all_env_var *var_dir);
void	double_quotes(t_current_command *command);
void	single_quotes(t_current_command *command);
void	special_into_normal(t_args *args, int arg, int i);
int		is_spec_char(char c);

#endif