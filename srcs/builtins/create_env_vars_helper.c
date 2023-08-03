/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_vars_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:08:59 by khorike           #+#    #+#             */
/*   Updated: 2023/08/03 22:42:37 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	add_env_var(t_env_var **head, char *key,
			char *value, bool is_shell_var)
{
	t_env_var	*new_var;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		exit(EXIT_FAILURE);
	new_var->key = ft_strdup(key);
	new_var->values = (char **)malloc(2 * sizeof(char *));
	if (!new_var->key || !new_var->values)
		exit(EXIT_FAILURE);
	new_var->values[0] = ft_strdup(value);
	if (!new_var->values[0])
		exit(EXIT_FAILURE);
	new_var->values[1] = NULL;
	new_var->num_values = 1;
	new_var->is_shell_var = is_shell_var;
	new_var->next = *head;
	*head = new_var;
}

void	set_initial_env_vars(t_env_var **head, char *path)
{
	add_env_var(head, "PWD", path, false);
	add_env_var(head, "SHLVL", "1", false);
	add_env_var(head, "_", "/usr/bin/env", false);
}
