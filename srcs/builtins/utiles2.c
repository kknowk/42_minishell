/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:25:01 by khorike           #+#    #+#             */
/*   Updated: 2023/07/24 14:31:06 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**return_null_free(char *str)
{
	ft_free(str);
	return (NULL);
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

int	is_valid_varname(char *varname)
{
	char	*p;

	if (varname[0] == '\0')
		return (SUCCESS);
	if (ft_isdigit((unsigned char)varname[0]))
		return (SUCCESS);
	p = varname;
	while (*p != '\0')
	{
		if (!ft_isalnum((unsigned char)*p) && *p != '_')
			return (SUCCESS);
		p++;
	}	
	return (FAILURE);
}
