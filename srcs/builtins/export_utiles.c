/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:00:31 by khorike           #+#    #+#             */
/*   Updated: 2023/07/28 14:19:01 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_equal(char *cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i] == '=')
		{
			if (i == 0)
				return (error_in_export(cmds));
			return (cmds);
		}
		i++;
	}
	return (NULL);
}

char	*error_in_export(char *str)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
	return (str);
}

char	*is_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (error_in_export(name));
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_' && name[i] != '=')
			return (error_in_export(name));
		i++;
	}
	return (NULL);
}

int	declare(t_env_var *head)
{
	t_env_var	*current;

	current = head;
	while (current)
	{
		printf("%s", "declare -x ");
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

// char	*get_next_var(char **cmds, char *s1)
// {
// 	int		i;

// 	i = 0;
// 	while (cmds[i])
// 	{
// 		if (ft_strcmp(cmds[i], s1))
// 		{
// 			s1 = search_equal(cmds + i + 1);
// 			if (!s1)
// 				return (NULL);
// 			return (s1);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }
