/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:13:18 by khorike           #+#    #+#             */
/*   Updated: 2023/07/31 14:55:16 by khorike          ###   ########.fr       */
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
		exit(1);
	}
}

static void	handle_values(t_expand *exp, char **values, char **result)
{
	int	i;

	if (values)
	{
		i = 0;
		while (values[i])
		{
			exp->value = values[i];
			temp_result(exp, result);
			if (values[i + 1])
				*result = ft_strjoin(*result, " ");
			i++;
		}
	}
	else
	{
		*result[ft_strlen(*result)] = '\0';
	}
}

static void	handle_dollar_sign_1(t_expand *exp, char *varname,
	char **result, t_env_var **head)
{
	char	**values;

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
	values = search(head, varname);
	handle_values(exp, values, result);
}

static void	handle_no_dollar_sign(t_expand *exp, char **result)
{
	char	*buffer;

	buffer = (char *)malloc(2 * sizeof(char));
	if (!buffer)
		exit(1);
	buffer[0] = *exp->start;
	buffer[1] = '\0';
	exp->temp = *result;
	*result = ft_strjoin(*result, buffer);
	if (!result)
		exit(1);
	ft_free(exp->temp);
	ft_free(buffer);
	exp->start++;
}

char	*expand_and_replace(char *input, t_env_var **head)
{
	char		varname[MAX_BUFFER_SIZE];
	char		*result;
	t_expand	exp;

	result = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
	if (!result)
		exit(1);
	result[0] = '\0';
	exp.start = input;
	while (*exp.start != '\0')
	{
		if (*exp.start == '$')
		{
			handle_dollar_sign_1(&exp, varname, &result, head);
		}
		else
		{
			handle_no_dollar_sign(&exp, &result);
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
