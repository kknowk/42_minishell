/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:32 by khorike           #+#    #+#             */
/*   Updated: 2023/08/04 20:47:51 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_printf(const char *msg, const char *path)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, path, ft_strlen(path));
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

static int	helper_execute(char *args[PATH_MAX],
				char **cmds, t_env_var **env_vars)
{
	char	command_path[PATH_MAX];
	char	**path_dirs;
	int		i;
	int		exec_status;

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
		exec_status = execute_command_from_path(command_path, cmds);
		if (exec_status != SUCCESS)
			return (exec_status);
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
