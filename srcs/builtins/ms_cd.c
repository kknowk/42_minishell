/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:08:10 by khorike           #+#    #+#             */
/*   Updated: 2023/07/16 15:32:56 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_permission(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		perror("stat failed");
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
	if (fd > 0)
	{
		write(STDERR_FILENO, "cd: not a directory", 19);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		close(fd);
		return (FAILURE);
	}
	close(fd);
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

int	ft_cd(t_directory *dir, char *path)
{
	char	resolved_path[PATH_MAX];

	if (ft_realpath(path, resolved_path) == NULL)
	{
		if (check_fd_o_dir(path) || check_permission(path))
			return (FAILURE);
		write(STDERR_FILENO, "cd: no such file or directory", 29);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	if (chdir(resolved_path) != 0)
	{
		write(STDERR_FILENO, "cd: no such file or directory", 29);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	ft_strlcpy(dir->path, resolved_path, sizeof(dir->path));
	return (SUCCESS);
}

// int	ft_pwd(t_directory *dir)
// {
// 	printf("%s\n", dir->path);
// 	return (SUCCESS);
// }

// int main(void)
// {
// 	t_directory	dir;
// 	if (getcwd(dir.path, sizeof(dir.path)) == NULL)
// 	{
// 		perror("getcwd() error");
// 		exit(1);
// 	}
// 	ft_cd(&dir, "../");
// 	// ft_cd(&dir, "aaaa");
// 	ft_pwd(&dir);
// 	return (0);
// }
