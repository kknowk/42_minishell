/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/30 11:51:08 by khorike          ###   ########.fr       */
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
		if (!cmds[j])
			exit(1);
		j++;
	}
	if (!cmds)
		return (1);
	if (cmds[0][0] == '\0')
		return (1);
	return (0);
}

static int	handle_export(char **cmds, t_env_var **env_vars)
{
	int		status;

	status = SUCCESS;
	if (!cmds[1])
		return (declare(*env_vars));
	status = ft_export(env_vars, cmds);
	if (status == EXIT_ERROR)
		exit(1);
	return (status);
}

static void	support_fork(char **cmds)
{
	if (ft_fork() == 0)
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

void	exec_from_bin(char **cmds, t_directory *dir)
{
	struct stat	s;

	if (stat(cmds[0], &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			printf("%s: is a directory\n", cmds[0]);
			dir->error.error_num = 126;
			return ;
		}
		else if (access(cmds[0], X_OK) == 0)
		{
			support_fork(cmds);
		}
	}
	else
		dir->error.error_num = execute_command(cmds[0], cmds) * 127;
	return ;
}

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int			i;

	i = 0;
	if (!ft_strcmp(cmds[0], "pwd"))
		dir->error.error_num = ft_pwd(dir);
	if (!ft_strcmp(cmds[0], "cd"))
		dir->error.error_num = ft_cd(dir, cmds[1], env_vars);
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit();
	if (!ft_strcmp(cmds[0], "env"))
		dir->error.error_num = ft_env(*env_vars);
	if (!ft_strcmp(cmds[0], "export"))
		dir->error.error_num = handle_export(cmds, env_vars);
	if (!ft_strcmp(cmds[0], "unset"))
		dir->error.error_num = ft_unset(env_vars, cmds);
	while (cmds[i])
		i++;
	if (!ft_strcmp(cmds[0], "echo"))
		dir->error.error_num = ft_echo(cmds, i - 1);
}

	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
