/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:40:41 by khorike           #+#    #+#             */
/*   Updated: 2023/07/24 17:35:21 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	helper_unset(t_env_var **head, char *key)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (SUCCESS);
		}	
		prev = current;
		current = current->next;
	}
	return (FAILURE);
}

static char	*error_in_unset(char *str)
{
	write(STDERR_FILENO, "minishell: unset: `", 20);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
	return (ft_strchr(str, '='));
}

static char	*is_valid_name_unset(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (error_in_unset(key));
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (error_in_unset(key));
		i++;
	}
	return (NULL);
}

int	ft_unset(t_env_var **head, char **keys)
{
	int		status;
	int		i;

	status = SUCCESS;
	i = 1;
	while (keys[i])
	{
		if (is_valid_name_unset(keys[i]))
			status = FAILURE;
		helper_unset(head, keys[i]);
		i++;
	}
	return (status);
}
