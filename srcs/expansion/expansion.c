/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:13:18 by khorike           #+#    #+#             */
/*   Updated: 2023/07/16 15:38:39 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include "builtins.h"

int	is_valid_varname(char *varname)
{
	char	*p;

	if (varname[0] == '\0')
		return (0);
	if (ft_isdigit((unsigned char)varname[0]))
		return (0);
	p = varname;
	while (*p != '\0')
	{
		if (!ft_isalnum((unsigned char)*p) && *p != '_')
			return (0);
		p++;
	}	
	return (1);
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

void	expand_and_print(char *input)
{
	char		varname[256];
	char		*start;
	char		*end;
	char		*value;

	start = input;
	while (*start != '\0')
	{
		if (*start == '$' && *(start + 1) == '{')
		{
			end = ft_strstr(start, "}");
			if (end)
			{
				strncpy(varname, start + 2, end - start - 2);
				varname[end - start - 2] = '\0';
				value = getenv(varname);
				if (value)
					printf("%s", value);
				start = end + 1;
			}
			else
				break ;
		}
		else
		{
			ft_putchar(*start);
			start++;
		}
	}
	printf("\n");
}

// int	main(int ac, char *av[])
// {
// 	(void)ac;
// 	if (has_error(av[1]))
// 		printf("Error!\n");
// 	else
// 		expand_and_print(av[1]);
// 	return (0);
// }
