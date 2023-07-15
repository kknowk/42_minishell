/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:40:41 by khorike           #+#    #+#             */
/*   Updated: 2023/07/15 13:48:02 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_env_var **head, char *key)
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

// int	main(void)
// {
// 	t_env_var	*env_vars = NULL;
// 	char *env_str1 = "KEY1=Value1";
// 	char *env_str2 = "KEY2=Value2";

// 	ft_export(&env_vars, env_str1);
// 	ft_export(&env_vars, env_str2);
// 	t_env_var *current = env_vars;
// 	while (current != NULL)
// 	{
// 		printf("Key: %s, Value: %s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	ft_unset(&env_vars, "KEY1");
// 	ft_unset(&env_vars, "KEY2");
// 	while (current != NULL)
// 	{
// 		printf("Key: %s, Value: %s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	current = env_vars;
// 	// t_env_var *next;
// 	// while (current != NULL)
// 	// {
// 	// 	next = current->next;
// 	// 	free(current->key);
// 	// 	free(current->value);
// 	// 	free(current);
// 	// 	current = next;
// 	// }
// 	return (0);
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
