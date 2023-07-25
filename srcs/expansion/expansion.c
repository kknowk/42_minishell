/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:13:18 by khorike           #+#    #+#             */
/*   Updated: 2023/07/25 14:51:32 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include "builtins.h"

static void	temp_result(t_expand *exp, char **result)
{
	exp->temp = *result;
	*result = ft_strjoin(*result, exp->value);
	ft_free(exp->temp);
	if (!result)
	{
		exp->malloc_error_2 = 1;
		return ;
	}
}

static void	handle_dollar_sign_1(t_expand *exp, char *varname,
	char **result, t_env_var **head)
{
	if (*(exp->start + 1) == '{')
	{
		exp->end = ft_strstr(exp->start, "}");
		if (exp->end)
		{
			ft_strlcpy(varname, exp->start + 2, exp->end - exp->start - 1);
			exp->start = exp->end + 1;
		}
	}
	else
	{
		exp->end = exp->start + 1;
		while (ft_isalnum(*exp->end) || *exp->end == '_')
			exp->end++;
		ft_strlcpy(varname, exp->start + 1, exp->end - exp->start);
		exp->start = exp->end;
	}
	exp->value = search(head, varname);
	if (exp->value)
		temp_result(exp, result);
	else if (exp->malloc_error_2 == 1)
		return ;
	else
		*result[ft_strlen(*result)] = '\0';
}

static char	*error_free_return(char *str, t_directory *dir)
{
	dir->malloc_error = 1;
	ft_free(str);
	return (NULL);
}

static void	handle_no_dollar_sign(t_expand *exp,
		char **result, t_directory *dir)
{
	char	*buffer;

	exp->malloc_error_2 = 0;
	buffer = (char *)malloc(2 * sizeof(char));
	if (!buffer)
	{
		dir->malloc_error = 1;
		return ;
	}
	buffer[0] = *exp->start;
	buffer[1] = '\0';
	exp->temp = *result;
	*result = ft_strjoin(*result, buffer);
	ft_free(exp->temp);
	ft_free(buffer);
	if (!result)
	{
		dir->malloc_error = 1;
		return ;
	}
	exp->start++;
}

char	*expand_and_replace(char *input, t_env_var **head, t_directory *dir)
{
	char		varname[MAX_BUFFER_SIZE];
	char		*result;
	t_expand	exp;

	result = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	exp.start = input;
	while (*exp.start != '\0')
	{
		if (*exp.start == '$')
		{
			handle_dollar_sign_1(&exp, varname, &result, head);
			if (exp.malloc_error_2 == 1)
				return (error_free_return(result, dir));
		}
		else
		{
			handle_no_dollar_sign(&exp, &result, dir);
			if (dir->malloc_error == 1)
				return (error_free_return(result, dir));
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
