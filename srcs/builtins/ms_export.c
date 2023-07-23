/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:47:53 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 19:07:35 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**ft_split_first(const char *s, char c)
{
	char	**arr;
	char	*location;

	arr = malloc(2 * sizeof(char *));
	if (!arr)
		return (NULL);
	location = ft_strchr(s, c);
	if (location)
	{
		arr[0] = ft_strndup(s, location - s);
		arr[1] = ft_strdup(location + 1);
	}
	else
	{
		arr[0] = ft_strdup(s);
		arr[1] = NULL;
	}
	return (arr);
}

static t_env_var	*find_node(t_env_var **head, char *key)
{
	t_env_var	*current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static int	type_existing_val(t_env_var *existing_node,
	char *value, char **split_result, char *key)
{
	free(existing_node->value);
	existing_node->value = value;
	free(split_result);
	free(key);
	return (SUCCESS);
}

int	ft_export(t_env_var **head, char *env_str)
{
	char		*key;
	char		*value;
	char		**split_result;
	t_env_var	*new_var;
	t_env_var	*existing_node;

	split_result = ft_split_first(env_str, '=');
	if (!split_result)
		return (error_failure("Splitting string failed", split_result));
	key = split_result[0];
	value = split_result[1];
	existing_node = find_node(head, key);
	if (existing_node)
		return (type_existing_val(existing_node, value, split_result, key));
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (error_failure("Memory allocation failed", split_result));
	new_var->key = key;
	new_var->value = value;
	new_var->is_shell_var = false;
	new_var->next = NULL;
	new_var->next = *head;
	*head = new_var;
	free(split_result);
	return (SUCCESS);
}
