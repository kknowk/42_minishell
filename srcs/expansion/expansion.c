/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:13:18 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 16:27:11 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include "builtins.h"

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

static void	temp_result(t_expand *exp, char **result)
{
	exp->temp = *result;
	*result = ft_strjoin(*result, exp->value);
	free(exp->temp);
	exp->temp = NULL;
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
	else
		*result[ft_strlen(*result)] = '\0';
}

static void	handle_no_dollar_sign(t_expand *exp, char **result)
{
	char	*buffer;

	buffer = (char *)malloc(2 * sizeof(char));
	if (!buffer)
		return ;
	buffer[0] = *exp->start;
	buffer[1] = '\0';
	exp->temp = *result;
	*result = ft_strjoin(*result, buffer);
	free(exp->temp);
	exp->temp = NULL;
	free(buffer);
	buffer = NULL;
	exp->start++;
}

char	*expand_and_replace(char *input, t_env_var **head)
{
	char		varname[256];
	char		*result;
	t_expand	exp;

	result = (char *)malloc(INT_MAX * sizeof(char));
	if (!result)
		return (NULL);
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
