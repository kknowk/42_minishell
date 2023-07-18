/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utility_comand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:32 by khorike           #+#    #+#             */
/*   Updated: 2023/07/18 17:39:44 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	execute_command_from_path(char *command_path,
		char **cmds)
{
	if (access(command_path, X_OK) == 0)
	{
		if (fork() == 0)
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

char	*add_current_directory_to_path(void)
{
	char	*original_path;
	char	cwd[PATH_MAX];
	char	*new_path;

	original_path = getenv("PATH");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		new_path = malloc(strlen(original_path) + strlen(cwd) + 2);
		if (new_path == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ms_cpca(new_path, original_path, ":", cwd);
		return (new_path);
	}
	else
	{
		perror("getcwd() error");
		return (NULL);
	}
}

static int	helper_execute(char	*args[PATH_MAX], char **cmds)
{
	char	*path;
	char	*path_copy;
	char	*path_token;
	char	command_path[PATH_MAX];

	path = add_current_directory_to_path();
	path_copy = ft_strdup(path);
	ms_free(path);
	if (path_copy == NULL)
		error_put("Memory allocation failed");
	path_token = ft_strtok(path_copy, ":");
	while (path_token != NULL)
	{
		ms_cpca(command_path, path_token, "/", args[0]);
		execute_command_from_path(command_path, cmds);
		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return (SUCCESS);
		}
		path_token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (error_str(args[0]));
}

int	execute_command(char *command, char **cmds)
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
	return (helper_execute(args, cmds));
}

// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// int	main(void)
// {
// 	char	*command;

// 	while (1)
// 	{
// 		command = readline(">> ");
// 		if (command == NULL)
// 			break ;
// 		if (strcmp(command, "exit") == 0)
// 		{
// 			free(command);
// 			break ;
// 		}
// 		add_history(command);
// 		execute_command(command);
// 		free(command);
// 	}
// 	return (0);
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
