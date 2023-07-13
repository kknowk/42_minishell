/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utility_comand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:32 by khorike           #+#    #+#             */
/*   Updated: 2023/07/13 19:15:35 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	execute_command_from_path(char *command_path,
		char *args[PATH_MAX])
{
	if (access(command_path, X_OK) == 0)
	{
		if (fork() == 0)
		{
			execve(command_path, args, NULL);
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

static void	error_put(char *str)
{
	perror(str);
	exit(1);
}

static void	error_str(char *str)
{
	write(STDERR_FILENO, "bash", 4);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": command not found", 19);
	write(STDERR_FILENO, "\n", 1);
}

static size_t	ft_strcspn(const char *s1r, const char *s2r)
{
	const char	*s1 = s1r;
	const char	*s2;

	while (*s1)
	{
		s2 = s2r;
		while (*s2)
		{
			if (*s1 == *s2++)
				return (s1 - s1r);
		}
		s1++;
	}
	return (s1 - s1r);
}

static size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t		count;

	count = 0;
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
			count++;
		else
			break ;
		s1++;
	}
	return (count);
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

static void	helper_execute(char	*args[PATH_MAX])
{
	char	*path;
	char	*path_copy;
	char	*path_token;
	char	command_path[PATH_MAX];

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	if (path_copy == NULL)
		error_put("Memory allocation failed");
	path_token = ft_strtok(path_copy, ":");
	while (path_token != NULL)
	{
		strcpy(command_path, path_token);
		strcat(command_path, "/");
		strcat(command_path, args[0]);
		execute_command_from_path(command_path, args);
		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return ;
		}
		path_token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	error_str(args[0]);
}

void	execute_command(char *command)
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
	helper_execute(args);
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
