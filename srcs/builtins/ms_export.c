/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:47:53 by khorike           #+#    #+#             */
/*   Updated: 2023/07/12 16:48:38 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_env_var **head, char *env_str)
{
	char		*key;
	char		*value;
	char		**split_result;
	t_env_var	*new_var;

	split_result = ft_split(env_str, '=');
	key = split_result[0];
	value = split_result[1];
	if (!split_result)
		return (error_failure("Splitting string failed"));
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (error_failure("Memory allocation failed"));
	new_var->key = split_result[0];
	new_var->value = split_result[1];
	new_var->is_shell_var = false;
	new_var->next = NULL;
	new_var->next = *head;
	*head = new_var;
	free(split_result);
	return (SUCCESS);
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
// 	current = env_vars;
// 	t_env_var *next;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// 	return (0);
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
>>>>>>> b19f72669f62552a416f65e5ae9fbe72d0888494
// }
