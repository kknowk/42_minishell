/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:57:29 by khorike           #+#    #+#             */
/*   Updated: 2023/07/12 14:06:58 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env_var *head)
{
	t_env_var	*current;

	current = head;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;

// 	// 環境変数の作成
// 	t_env_var *env_vars = create_env_vars(envp);
// 	// 環境変数の表示
// 	t_env_var *current = env_vars;
// 	ft_env(current);
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
