/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:41:58 by khorike           #+#    #+#             */
/*   Updated: 2023/08/01 18:58:17 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_from_bin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	struct stat	s;

	if (judgement_desuno(cmds, dir, env_vars))
		return ;
	if (stat(cmds[0], &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			error_printf("minishell: is a directory\n", cmds[0]);
			dir->error.error_num = 126;
			return ;
		}
		else if (access(cmds[0], X_OK) == 0)
		{
			support_fork(cmds);
		}
	}
	else
		dir->error.error_num = execute_command(cmds[0], cmds, env_vars) * 127;
	return ;
}
