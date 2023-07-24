/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:33:45 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 13:33:36 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	error_failure(char *str, char **str1)
{
	if (str1)
		free(str1);
	perror(str);
	return (FAILURE);
}

void	error_put(char *str)
{
	perror(str);
	exit(1);
}

int	error_str(char *str)
{
	write(STDERR_FILENO, "bash", 4);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": command not found", 19);
	write(STDERR_FILENO, "\n", 1);
	return (FAILURE);
}

size_t	ft_strcspn(const char *s1r, const char *s2r)
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

size_t	ft_strspn(const char *s1, const char *s2)
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
