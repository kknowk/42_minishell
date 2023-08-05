/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:32 by khorike           #+#    #+#             */
/*   Updated: 2023/08/04 14:03:20 by khorike          ###   ########.fr       */
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
	while (tmp)
	{
		if (!(tmp + 1)[0])
			break ;
		if ((tmp + 1)[0] == '?')
		{
			str = handle_question_mark(str, tmp, dir);
		}
		else if ((tmp + 1)[0] == '$')
			str = handle_dollar_sign(str, tmp);
		else
		{
			str = handle_default(str, tmp, head);
		}
		if (!str)
			break ;
		tmp = ft_strchr(str, '$');
	}
	return (str);
}

// char *dollar_handle(char *str, t_directory *dir, t_env_var **head)
// {
//     char *start, *end;
//     char *result = NULL;
//     char *substring = NULL;
//     int len;

//     start = str;
//     while (start)
//     {
//         end = ft_strchr(start + 1, '$');
//         // If two '$'s are consecutive, consider them as one unit.
//         if (end && *(end - 1) == '$')
//         {
//             end++;
//         }

//         len = end ? end - start : ft_strlen(start);
//         substring = ft_substr(start, 0, len);

//         if (substring[0] == '$')
//         {
//             if (substring[1] == '?')
//             {
//                 substring = handle_question_mark(substring, substring, dir);
//             }
//             else if (substring[1] == '$')
//             {
//                 substring = handle_dollar_sign(substring, substring);
//             }
//             else
//             {
//                 substring = handle_default(substring, substring, head);
//             }
//         }

//         result = ft_strjoin(result, substring);
//         start = end;
//     }

//     return result;
// }
