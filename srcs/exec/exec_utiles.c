/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:06:54 by khorike           #+#    #+#             */
/*   Updated: 2023/08/05 12:16:25 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_file_permission(char *path, t_directory *dir)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		write(STDERR_FILENO, "minishell: No such file or directory", 36);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		dir->error.error_num = 127;
		return (false);
	}
	if ((statbuf.st_mode & S_IRUSR) == 0)
	{
		write(STDERR_FILENO, "minishell: Permission denied", 28);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		dir->error.error_num = 126;
		return (false);
	}
	return (true);
}

bool	check_fd_or_dir(char *path, t_directory *dir)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (fd > 0)
	{
		write(STDERR_FILENO, "minishell: command not found", 28);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "\n", 1);
		ft_close(fd);
		dir->error.error_num = 127;
		return (false);
	}
	ft_close(fd);
	return (true);
}
