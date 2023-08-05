/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:08:10 by khorike           #+#    #+#             */
/*   Updated: 2023/08/05 12:29:47 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_permission(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		write(STDERR_FILENO, "cd: No such file or directory", 29);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	if ((statbuf.st_mode & S_IRUSR) == 0)
	{
		write(STDERR_FILENO, "cd: Permission denied", 21);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_fd_o_dir(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (fd > 0)
	{
		write(STDERR_FILENO, "cd: Not a directory", 19);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		ft_close(fd);
		return (FAILURE);
	}
	ft_close(fd);
	return (SUCCESS);
}

static char	*ft_realpath(const char *path, char *resolved_path)
{
	if (path == NULL || resolved_path == NULL)
		return (NULL);
	if (chdir(path) != 0)
		return (NULL);
	if (getcwd(resolved_path, PATH_MAX) == NULL)
		return (NULL);
	return (resolved_path);
}

static int	home(t_directory *dir, t_env_var **head)
{
	char	*home;

	home = *search(head, "HOME");
	if (!home)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 18);
		return (FAILURE);
	}
	chdir(home);
	ft_strlcpy(dir->path, home, sizeof(dir->path));
	return (SUCCESS);
}

int	ft_cd(t_directory *dir, char *path, t_env_var **head)
{
	char	resolved_path[PATH_MAX];

	if (!path || path[0] == '~')
		return (home(dir, head));
	if (ft_realpath(path, resolved_path) == NULL)
	{
		if (check_permission(path) || check_fd_o_dir(path))
			return (FAILURE);
		write(STDERR_FILENO, "cd: No such file or directory", 29);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	if (chdir(resolved_path) != 0)
	{
		write(STDERR_FILENO, "cd: No such file or directory", 29);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	ft_strlcpy(dir->path, resolved_path, sizeof(dir->path));
	return (SUCCESS);
}
