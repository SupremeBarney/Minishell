/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/29 17:28:34 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char *str, char **args, t_shell *shell)
{
	t_exec_info	info;
	t_env		*parseur;

	if (!shell->env)
		return ;
	parseur = shell->env;
	info.pwd = NULL;
	while (parseur)
	{
		if (ft_strncmp("PWD", parseur->name, 4) == 0)
			info.pwd = ft_strdup(parseur->value);
		parseur = parseur->next;
	}
	info.envp = ft_envp(shell->env);
	info.shell = shell;
	ft_which_exec(str, args, &info);
	free(info.pwd);
	free_chars(info.envp);
}

void	ft_which_exec(char *str, char **args, t_exec_info *info)
{
	if (!str)
	{
		//error
		return ;
	}
	else if (ft_strncmp(str, "./", 2) == 0)
	{
		ft_exec_relative_path(str, args, info);
	}
	else if (str[0] == '/')
	{
		ft_exec_true_path(str, args, info);
		return ;
	}
}

static int	ft_is_dir(char *str)
{
	struct stat	st;

	if (stat(str, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

static void	ft_exec_child_error(char *str)
{
	int	err;

	err = errno;
	ft_putstr_fd("bash: ", 2);
	perror(str);
	if (err == EACCES)
		exit(126);
	exit(127);
}

void	ft_exec_true_path(char *str, char **args, t_exec_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_is_dir(str))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit(126);
		}
		if (execve(str, args, info->envp) == -1)
			ft_exec_child_error(str);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		info->shell->exit_status = wait_status_to_code(status);
	}
	if (pid < 0)
		perror("Eror");
}

static void	ft_exec_rel_child(char *str, char **args, t_exec_info *info)
{
	char	*ret;
	char	*tmp;
	char	*name;

	tmp = ft_strjoin(info->pwd, "/");
	name = ft_enlever_str(str);
	ret = ft_strjoin(tmp, name);
	free(tmp);
	free(name);
	if (ft_is_dir(ret))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (execve(ret, args, info->envp) == -1)
		ft_exec_child_error(str);
}

void	ft_exec_relative_path(char *str, char **args, t_exec_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		ft_exec_rel_child(str, args, info);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		info->shell->exit_status = wait_status_to_code(status);
	}
	if (pid < 0)
		perror("EROROR");
}

char	*ft_enlever_str(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(str) - 1);
	while (str[i + 2])
	{
		ret[i] = str[i + 2];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	ft_env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_envp(t_env *first_env)
{
	char	**ret;
	int		i;
	t_env	*parseur;
	char	*tmp;

	ret = malloc(sizeof(char *) * (ft_env_len(first_env) + 1));
	i = 0;
	parseur = first_env;
	while (parseur)
	{
		if (parseur->equal == 1)
		{
			tmp = ft_strjoin(parseur->name, "=");
			ret[i] = ft_strjoin(tmp, parseur->value);
			free (tmp);
			i++;
		}
		parseur = parseur->next;
	}
	ret[i] = NULL;
	return (ret);
}
