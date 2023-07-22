/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/22 21:45:33 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int	j;

	if (cmds[0] == NULL)
		return (1);
	j = 0;
	while (cmds[j])
	{
		if (is_quoted(cmds[j]))
			cmds[j] = quote_handle(cmds[j], dir, env_vars);
		else
			cmds[j] = dollar_handle(cmds[j], dir, env_vars);
		j++;
	}
	if (!cmds)
		return (1);
	if (cmds[0][0] == '\0')
		return (1);
	return (0);
}

static int	sub(char **cmds, t_env_var **env_vars)
{
	if (ft_export(env_vars, cmds[1])) // exportの引数がない場合は、env_varsの中身を表示するのでは？
		exit(1);
	else
		return (0);
}

static void	support_fork(char **cmds)
{
	if (fork() == 0)
	{
		execve(cmds[0], cmds, NULL);
		perror("execve failed");
		exit(1);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

static void	expansion(char **cmds, t_directory *dir)
{
	struct stat	s;

	if (stat(cmds[0], &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			printf("%s: is a directory\n", cmds[0]);
			dir->error = 126;
			return ;
		}
		else if (access(cmds[0], X_OK) == 0)
		{
			support_fork(cmds);
		}
	}
	else
		dir->error = execute_command(cmds[0], cmds) * 127;
	return ;
}

void	exec_builtin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int			i;

	i = 0;
	if (judgement_desuno(cmds, dir, env_vars) == 1)
		return ;
	if (!ft_strcmp(cmds[0], "pwd"))
		dir->error = ft_pwd(dir);
	if (!ft_strcmp(cmds[0], "cd"))
		dir->error = ft_cd(dir, cmds[1], env_vars);
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit();
	if (!ft_strcmp(cmds[0], "env"))
		dir->error = ft_env(*env_vars);
	if (!ft_strcmp(cmds[0], "export"))
		dir->error = sub(cmds, env_vars);
	if (!ft_strcmp(cmds[0], "unset"))
		dir->error = ft_unset(env_vars, cmds[1]);
	while (cmds[i])
		i++;
	if (!ft_strcmp(cmds[0], "echo"))
		dir->error = ft_echo(cmds, i - 1);
	else if (ft_strcmp(cmds[0], "cd") && ft_strcmp(cmds[0], "pwd")
		&& ft_strcmp(cmds[0], "unset"))
		expansion(cmds, dir);
}

	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
