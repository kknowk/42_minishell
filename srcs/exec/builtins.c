/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/24 17:18:04 by khorike          ###   ########.fr       */
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

// int	ft_export_return(char *s1)
// {
// 	ft_free(s1);
// 	printf("exit\n");
// 	retunr (SUCCESS);
// }

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

void	exec_from_bin(char **cmds, t_directory *dir)
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

void	select_builtin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int			i;

	i = 0;
	if (!ft_strcmp(cmds[0], "pwd"))
		dir->error = ft_pwd(dir);
	if (!ft_strcmp(cmds[0], "cd"))
		dir->error = ft_cd(dir, cmds[1], env_vars);
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit();
	if (!ft_strcmp(cmds[0], "env"))
		dir->error = ft_env(*env_vars);
	if (!ft_strcmp(cmds[0], "export"))
		dir->error = handle_export(cmds, env_vars);
	if (!ft_strcmp(cmds[0], "unset"))
		dir->error = ft_unset(env_vars, cmds);
	while (cmds[i])
		i++;
	if (!ft_strcmp(cmds[0], "echo"))
		dir->error = ft_echo(cmds, i - 1);
}

	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
