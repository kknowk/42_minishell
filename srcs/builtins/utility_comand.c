/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:32 by khorike           #+#    #+#             */
/*   Updated: 2023/08/01 18:57:25 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_printf(const char *msg, const char *path)
{
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, path, strlen(path));
	write(STDERR_FILENO, "\n", 1);
}

static char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token;

	if (str != NULL)
		last_token = str;
	if (last_token == NULL || *last_token == '\0')
		return (NULL);
	last_token += ft_strspn(last_token, delim);
	token = last_token;
	last_token += ft_strcspn(last_token, delim);
	if (*last_token != '\0')
		*last_token++ = '\0';
	return (token);
}

static void	execute_command_from_path(char *command_path, char **cmds)
{
	struct stat	s;

	if (stat(command_path, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			error_printf("minishell: is a directory\n", command_path);
			return ;
		}
		else if (access(command_path, X_OK) == 0)
		{
			if (ft_fork() == 0)
			{
				execve(command_path, cmds, NULL);
				perror("execve failed");
				exit(1);
			}
			else
			{
				wait(NULL);
				return ;
			}
		}
	}
}

static int	helper_execute(char *args[PATH_MAX],
				char **cmds, t_env_var **env_vars)
{
	char	command_path[PATH_MAX];
	char	**path_dirs;
	int		i;

	path_dirs = search(env_vars, "PATH");
	if (path_dirs == NULL)
	{
		printf("%s: No such file or directory\n", args[0]);
		return (FAILURE);
	}
	i = 0;
	while (path_dirs[i])
	{
		ms_cpca(command_path, path_dirs[i], "/", args[0]);
		execute_command_from_path(command_path, cmds);
		if (access(command_path, X_OK) == 0)
		{
			return (SUCCESS);
		}
		i++;
	}
	return (error_str(args[0]));
}

int	execute_command(char *command, char **cmds, t_env_var **env_vars)
{
	char	command_buffer[PATH_MAX];
	char	*command_name;
	char	*args[PATH_MAX];
	int		args_count;

	ft_strlcpy(command_buffer, command, ft_strlen(command) + 1);
	command_name = ft_strtok(command_buffer, " ");
	args_count = 0;
	while (command_name != NULL)
	{
		args[args_count] = command_name;
		command_name = ft_strtok(NULL, " ");
		args_count++;
	}
	args[args_count] = NULL;
	return (helper_execute(args, cmds, env_vars));
}
