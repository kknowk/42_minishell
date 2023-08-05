/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_handle_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:07:28 by khorike           #+#    #+#             */
/*   Updated: 2023/08/05 12:33:11 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*cpy_itoa(char *tmp, char *str, t_directory *dir)
{
	char	*num;
	char	*result;

	num = ft_itoa(dir->error.error_num);
	if (!num)
		exit(EXIT_FAILURE);
	result = malloc(ft_strlen(str) + ft_strlen(num) - 1);
	if (!result)
	{
		ft_free(num);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(result, str, tmp - str);
	result[tmp - str] = '\0';
	ft_strcat(result, num);
	ft_strcat(result, tmp + 2);
	ft_free(num);
	return (result);
}

static char	*cpy_itoa_dd(char *tmp, char *str)
{
	char	*num;
	char	*result;

	num = ft_itoa(20870);
	if (!num)
		exit(EXIT_FAILURE);
	result = malloc(ft_strlen(str) + ft_strlen(num) - 1);
	if (!result)
	{
		ft_free(num);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(result, str, tmp - str);
	result[tmp - str] = '\0';
	ft_strcat(result, num);
	ft_strcat(result, tmp + 2);
	ft_free(num);
	return (result);
}

char	*handle_question_mark(char *str, char *tmp, t_directory *dir)
{
	char	*processed;

	processed = cpy_itoa(tmp, str, dir);
	if (processed)
	{
		ft_free(str);
		str = processed;
	}
	else
		ft_free(str);
	return (str);
}

char	*handle_dollar_sign(char *str, char *tmp)
{
	char	*processed;

	processed = cpy_itoa_dd(tmp, str);
	if (processed)
	{
		ft_free(str);
		str = processed;
	}
	else
		ft_free(str);
	return (str);
}

char	*handle_default(char *str, t_env_var **head)
{
	char	*processed;

	processed = expand_and_replace(str, head);
	if (processed)
	{
		ft_free(str);
		str = processed;
	}
	else
		ft_free(str);
	return (str);
}
