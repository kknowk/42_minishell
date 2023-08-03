/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_comand_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:07:29 by khorike           #+#    #+#             */
/*   Updated: 2023/08/02 17:21:01 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	execute_in_child_process(char *command_path, char **cmds)
{
	execve(command_path, cmds, NULL);
	perror("execve failed");
	exit(1);
}

static int	handle_child_execution(char *command_path, char **cmds)
{
	int	status;

	if (ft_fork() == 0)
	{
		execute_in_child_process(command_path, cmds);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

int	execute_command_from_path(char *command_path, char **cmds)
{
	struct stat	s;

	if (stat(command_path, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			error_printf("minishell: is a directory\n", command_path);
			return (FAILURE);
		}
		else if (access(command_path, X_OK) == 0)
		{
			return (handle_child_execution(command_path, cmds));
		}
	}
	return (SUCCESS);
}
