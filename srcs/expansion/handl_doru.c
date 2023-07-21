/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_doru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:32 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 16:24:05 by khorike          ###   ########.fr       */
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

char	*doru_handl(char *str, t_directory *dir, t_env_var **head)
{
	char	*tmp;

	tmp = ft_strchr(str, '$');
	if (!tmp)
		return (str);
	while (tmp)
	{
		if ((tmp + 1)[0] == '?')
			str = handle_question_mark(str, tmp, dir);
		else if ((tmp + 1)[0] == '$')
			str = handle_dollar_sign(str, tmp);
		else
			str = handle_default(str, tmp, head);
		if (!str)
			break ;
		tmp = ft_strchr(str, '$');
	}
	return (str);
}
