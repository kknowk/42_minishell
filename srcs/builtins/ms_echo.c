/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:48:01 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 12:29:21 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

// static int	ft_memcmp(const void *s1, const void *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (str1[i] != str2[i])
// 			return (str1[i] - str2[i]);
// 		i++;
// 	}
// 	return (0);
// }

static void	helper_ft_echo(char **str, int max_words)
{
	int	i;

	i = 1;
	while (i < max_words)
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("%s", str[i]);
	printf("\n");
}

int	ft_echo(char **str, int max_words)
{
	int	i;

	i = 1;
	if (str[1] == NULL)
	{
		printf("\n");
		return (SUCCESS);
	}
	if (ft_memcmp(str[1], "-n", 3) == 0)
	{
		i++;
		while (i < max_words)
		{
			printf("%s ", str[i]);
			i++;
		}
		if (str[i])
		{
			ft_putstr(str[i]);
		}
	}
	else
		helper_ft_echo(str, max_words);
	return (SUCCESS);
}

// int	main(int ac, char *av[])
// {
// 	ft_echo(av + 1, ac - 1);
// }
