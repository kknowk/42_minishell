/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utility_comand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:32 by khorike           #+#    #+#             */
/*   Updated: 2023/07/12 21:01:50 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*cpy;

	len = ft_strlen(s1);
	cpy = malloc(sizeof(char) * (len + 1));
	if (cpy == NULL)
		perror("malloc failed");
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static void	execute_command_from_path(char *command_path,
		char *args[MAX_COMMAND_LENGTH])
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
	write(STDERR_FILENO, "bash: command not found", 19);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

static void	helper_execute(char	*args[MAX_COMMAND_LENGTH])
{
	char	*path;
	char	*path_copy;
	char	*path_token;
	char	command_path[MAX_COMMAND_LENGTH];

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	if (path_copy == NULL)
		error_put("Memory allocation failed");
	path_token = strtok(path_copy, ":");
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
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	fprintf(stderr, "Command not found: %s\n", args[0]);
}

void	execute_command(char *command)
{
	char	command_buffer[MAX_COMMAND_LENGTH];
	char	*command_name;
	char	*args[MAX_COMMAND_LENGTH];
	int		args_count;

	strcpy(command_buffer, command);
	command_name = strtok(command_buffer, " ");
	args_count = 0;
	while (command_name != NULL)
	{
		args[args_count] = command_name;
		command_name = strtok(NULL, " ");
		args_count++;
	}
	args[args_count] = NULL;
	helper_execute(args);
}

#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*command;

	while (1)
	{
		command = readline(">> ");
		if (command == NULL)
			break ;
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		add_history(command);
		execute_command(command);
		free(command);
	}
	return (0);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}
