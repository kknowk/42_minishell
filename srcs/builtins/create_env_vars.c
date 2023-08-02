/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:30:19 by khorike           #+#    #+#             */
/*   Updated: 2023/08/02 13:09:39 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

static t_env_var	*check_split(t_env_var *head)
{
	t_env_var	*current;
	t_env_var	*next;
	int			i;

	current = head;
	while (current)
	{
		next = current->next;
		ft_free(current->key);
		i = 0;
		while (i < current->num_values)
		{
			ft_free(current->values[i]);
			i++;
		}
		ft_free(current->values);
		ft_free(current);
		current = next;
	}
	return (NULL);
}

static t_env_var	*init_new_var(char *key, char *value, bool is_shell_var)
{
	t_env_var	*new_var;
	char		**p;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	new_var->values = ft_split(value, ':');
	if (!new_var->values)
		exit(1);
	new_var->num_values = 0;
	p = new_var->values;
	while (*p)
	{
		new_var->num_values++;
		p++;
	}
	new_var->key = key;
	ft_free(value);
	new_var->is_shell_var = is_shell_var;
	new_var->next = NULL;
	return (new_var);
}

static void	helper_env(char **split_result, t_env_var **head, t_env_var **prev)
{
	char		*key;
	char		*value;
	t_env_var	*new_var;

	key = split_result[0];
	value = split_result[1];
	new_var = init_new_var(key, value, false);
	if (*prev == NULL)
		*head = new_var;
	else
		(*prev)->next = new_var;
	*prev = new_var;
	ft_free(split_result);
}

t_env_var	*create_env_vars(char *envp[], char *path)
{
	t_env_var	*head;
	t_env_var	*prev;
	int			i;
	char		**split_result;

	i = 0;
	head = NULL;
	prev = NULL;
	if (envp[i] == NULL)
	{
		set_initial_env_vars(&head, path);
		return (head);
	}
	while (envp[i] != NULL)
	{
		split_result = ft_split(envp[i], '=');
		if (!split_result)
			return (check_split(head));
		helper_env(split_result, &head, &prev);
		i++;
	}
	return (head);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;

// 	// 環境変数の作成
// 	t_env_var *env_vars = create_env_vars(envp);
// 	// 環境変数の表示
// 	t_env_var *current = env_vars;
// 	while (current)
// 	{
// 		printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}	
// 	// 環境変数の解放
// 	current = env_vars;
// 	while (current)
// 	{
// 		t_env_var *next = current->next;
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
// }
