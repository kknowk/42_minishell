/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utiles2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:25:01 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 15:15:18 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_free(char *str)
{
	if (str)
	{
		free(str);
	}
}

void	ms_cpca(char *s1, char *s2, char *s3, char *s4)
{
	ft_strcpy(s1, s2);
	ft_strcat(s1, s3);
	ft_strcat(s1, s4);
}

int	has_error(char *input)
{
	char		varname[256];
	char		*start;
	char		*end;

	start = input;
	while (*start != '\0')
	{
		if (*start == '$' && *(start + 1) == '{')
		{
			end = ft_strstr(start, "}");
			if (end)
			{
				ft_strlcpy(varname, start + 2, end - start - 2 + 1);
				if (!is_valid_varname(varname))
					return (1);
				start = end + 1;
			}
			else
				return (1);
		}
		else
			start++;
	}
	return (0);
}
