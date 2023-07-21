/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 19:21:24 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

static int	judgment_desuno(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int	j;

	if (cmds[0] == NULL)
		return (1);
	j = 0;
	while (cmds[j])
	{
		if (is_quoted(cmds[j]))
			cmds[j] = quot_handl(cmds[j], dir, env_vars);
		else
			cmds[j] = doru_handl(cmds[j], dir, env_vars);
		j++;
	}
	if (!cmds)
		return (1);
	if (cmds[0][0] == '\0')
		return (1);
	return (0);
}

static void	sub(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	if (ft_export(env_vars, cmds[1]))
		exit(1);
	else
		dir->error = 0;
	return ;
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

void	ft_select(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int			i;

	i = 0;
	if (judgment_desuno(cmds, dir, env_vars) == 1)
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
		return (sub(cmds, dir, env_vars));
	if (!ft_strcmp(cmds[0], "unset"))
		dir->error = ft_unset(env_vars, cmds[1]);
	while (cmds[i])
		i++;
	if (!ft_strcmp(cmds[0], "echo"))
		ft_echo(cmds, i - 1);
	else if (ft_strcmp(cmds[0], "cd") && ft_strcmp(cmds[0], "pwd")
		&& ft_strcmp(cmds[0], "unset"))
		return (expansion(cmds, dir));
}

	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
