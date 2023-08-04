/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:06:54 by khorike           #+#    #+#             */
/*   Updated: 2023/08/04 14:14:31 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_permission(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		write(STDERR_FILENO, "minishell: No such file or directory", 36);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	if ((statbuf.st_mode & S_IRUSR) == 0)
	{
		write(STDERR_FILENO, "minishell: Permission denied", 28);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (FAILURE);
	}
	return (SUCCESS);
}
