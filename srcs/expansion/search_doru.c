/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_doru.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:32 by khorike           #+#    #+#             */
/*   Updated: 2023/07/17 14:34:33 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*search(t_env_var **head, char *key)
{
	t_env_var	*current;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*cpy_itoa(char *tmp, char *str, char *common, t_directory *dir)
{
	char	*num;
	char	*num2;

	num = ft_itoa(dir->error);
	num2 = ft_itoa(127);
	if (num && num2)
	{
		if (dir->error != 127)
		{
			ft_strlcpy(common, str, (tmp - str) + 1);
			ft_strlcpy(common + (tmp - str), num, 2);
			ft_strlcpy(common + (tmp - str) + 1, tmp + 2, ft_strlen(tmp) - 1);
			free(num);
		}
		else
		{
			ft_strlcpy(common, str, (tmp - str) + 1);
			ft_strlcpy(common + (tmp - str), num2, 4);
			ft_strlcpy(common + (tmp - str) + 3, tmp + 2, ft_strlen(tmp) - 1);
			free(num2);
		}
		return (common);
	}
	return (NULL);
}

char	*doru_handl(char *str, t_directory *dir, t_env_var **head)
{
	char	*tmp;
	char	*common;
	char	*processed;

	tmp = ft_strchr(str, '$');
	if (!tmp)
		return (str);
	common = (char *)malloc(INT_MAX * sizeof(char));
	if (!common)
		return (NULL);
	while (tmp)
	{
		if ((tmp + 1)[0] == '?')
		{
			processed = cpy_itoa(tmp, str, common, dir);
			if (processed)
			{
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
				str = processed;
				tmp = ft_strchr(str, '$');
			}
			else
				break ;
		}
	}
	return (str);
}
