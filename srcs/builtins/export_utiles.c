/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:00:31 by khorike           #+#    #+#             */
/*   Updated: 2023/08/01 17:05:48 by khorike          ###   ########.fr       */
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
		if (!ft_isalnum(name[i]) && name[i] != '_' && name[i] != '='
			&& name[i] != ':')
			return (error_in_export(name));
		i++;
	}
	return (NULL);
}

int	declare(t_env_var *head)
{
	t_env_var	*current;
	int			i;

	current = head;
	while (current)
	{
		i = 0;
		printf("%s", "declare -x ");
		printf("%s=", current->key);
		while (i < current->num_values)
		{
			printf("\"%s\"", current->values[i]);
			if (i < current->num_values - 1)
				printf("%s", ":");
			i++;
		}
		printf("%s", "\n");
		current = current->next;
	}
	return (SUCCESS);
}

int	ft_count_values(char **values)
{
	int	i;

	i = 0;
	while (values[i])
		i++;
	return (i);
}
