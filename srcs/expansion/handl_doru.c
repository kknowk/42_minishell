/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_doru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:32 by khorike           #+#    #+#             */
/*   Updated: 2023/07/19 19:00:25 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*search(t_env_var **head, char *key)
{
	t_env_var	*current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

static char	*cpy_itoa(char *tmp, char *str, t_directory *dir)
{
	char	*num;
	char	*result;

	num = ft_itoa(dir->error);
	if (!num)
		return (NULL);
	result = malloc(ft_strlen(str) + ft_strlen(num) - 1);
	if (!result)
	{
		free(num);
		return (NULL);
	}
	ft_memcpy(result, str, tmp - str);
	result[tmp - str] = '\0';
	ft_strcat(result, num);
	ft_strcat(result, tmp + 2);
	free(num);
	return (result);
}

char	*doru_handl(char *str, t_directory *dir, t_env_var **head)
{
	char	*tmp;
	char	*processed;

	tmp = ft_strchr(str, '$');
	if (!tmp)
		return (str);
	while (tmp)
	{
		if ((tmp + 1)[0] == '?')
		{
			processed = cpy_itoa(tmp, str, dir);
			if (processed)
			{
				free(str);
				str = processed;
				tmp = ft_strchr(str, '$');
			}
			else
				break ;
		}
		else
		{
			processed = expand_and_replace(str, head);
			if (processed)
			{
				free(str);
				str = processed;
				tmp = ft_strchr(str, '$');
			}
			else
				break ;
		}
	}
	return (str);
}
