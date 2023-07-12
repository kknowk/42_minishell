/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:08:10 by khorike           #+#    #+#             */
/*   Updated: 2023/07/12 16:52:59 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// static size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	if (s == NULL)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// static void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t		i;
// 	char		*to;
// 	const char	*from;

// 	to = (char *)dst;
// 	from = (const char *)src;
// 	if (dst == NULL && src == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		to[i] = from[i];
// 		i++;
// 	}
// 	return (dst);
// }

// static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	srclen;

// 	srclen = ft_strlen(src);
// 	if (srclen + 1 < dstsize)
// 	{
// 		ft_memcpy(dst, src, srclen + 1);
// 		dst[srclen] = '\0';
// 	}
// 	else if (dstsize != 0)
// 	{
// 		ft_memcpy(dst, src, dstsize - 1);
// 		dst[dstsize - 1] = '\0';
// 	}
// 	return (srclen);
// }

char	*ft_realpath(const char *path, char *resolved_path)
{
	if (path == NULL || resolved_path == NULL)
		return (NULL);
	if (chdir(path) != 0)
	{
		perror("chdir() error");
		return (NULL);
	}
	if (getcwd(resolved_path, PATH_MAX) == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	return (resolved_path);
}

int	ft_cd(t_directory *dir, char *path)
{
	char	resolved_path[PATH_MAX];

	if (ft_realpath(path, resolved_path) == NULL)
	{
		write(STDERR_FILENO, "cd: no such file or directory", 19);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	if (chdir(resolved_path) != 0)
	{
		write(STDERR_FILENO, "cd: no such file or directory", 19);
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
