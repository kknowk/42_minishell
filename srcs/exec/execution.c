/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 15:30:04 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_nodes(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(node, dir, env_vars);
	else
	{
		if (is_builtins(node->data[0]))
		{
			if (judgement_desuno(node->data, dir, env_vars) == 1)
				return ;
			dir->error = exec_builtin(node->data, dir, env_vars);
		}
		else
			expansion(node->data, dir);
	}
}
