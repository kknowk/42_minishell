/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:13:18 by khorike           #+#    #+#             */
/*   Updated: 2023/07/19 18:55:35 by khorike          ###   ########.fr       */
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

char	*expand_and_replace(char *input, t_env_var **head)
{
	char		varname[256];
	char		*start;
	char		*end;
	char		*value;
	char		*result;
	char		*buffer;
	char		*temp;

	result = (char *)malloc(INT_MAX * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	start = input;
	while (*start != '\0')
	{
		if (*start == '$')
		{
			if (*(start + 1) == '{')
			{
				end = ft_strstr(start, "}");
				if (end)
				{
					ft_strlcpy(varname, start + 2, end - start - 1);
					start = end + 1;
				}
				else
					break ;
			}
			else
			{
				end = start + 1;
				while (ft_isalnum(*end) || *end == '_')
					end++;
				ft_strlcpy(varname, start + 1, end - start);
				start = end;
			}
			value = search(head, varname);
			if (value)
			{
				temp = result;
				result = ft_strjoin(result, value);
				free(temp);
			}
			else
			{
				result[ft_strlen(result)] = '\0';
				return (result);
			}
		}
		else
		{
			buffer = (char *)malloc(2 * sizeof(char));
			if (!buffer)
				return (NULL);
			buffer[0] = *start;
			buffer[1] = '\0';
			temp = result;
			result = ft_strjoin(result, buffer);
			free(temp);
			free(buffer);
			start++;
		}
	}
	return (result);
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
