/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:32 by khorike           #+#    #+#             */
/*   Updated: 2023/08/12 13:15:20 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**search(t_env_var **head, char *key)
{
	t_env_var	*current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			return (current->values);
		}
		current = current->next;
	}
	return (NULL);
}

char	*dollar_handle(char *str, t_directory *dir, t_env_var **head)
{
	char	*tmp;

	tmp = ft_strchr(str, '$');
	if (!tmp || !tmp[1])
		return (str);
	while (tmp && *tmp)
	{
		if (!*(tmp + 1))
			break ;
		if (*(tmp + 1) == '?')
			str = handle_question_mark(str, tmp, dir);
		else if (*(tmp + 1) == '$')
			str = handle_dollar_sign(str, tmp);
		else
			str = handle_default(str, head);
		if (!str)
			break ;
		tmp = ft_strchr(str, '$');
	}
	return (str);
}
