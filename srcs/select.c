/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/13 19:00:45 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	ft_select(t_token *token, t_directory *dir, t_env_var **env_vars)
{
	t_env_var	*current;

	current = *env_vars;
	if (!ft_strcmp(token->data, "pwd"))
		ft_pwd(dir);
	if (!ft_strcmp(token->data, "cd"))
		ft_cd(dir, token->next->data);
	if (!ft_strcmp(token->data, "exit"))
		ft_exit();
	if (!ft_strcmp(token->data, "env"))
		ft_env(*env_vars);
	if (!ft_strcmp(token->data, "export"))
	{
		if (ft_export(env_vars, token->next->data))
			exit(1);
	}
	if (!ft_strcmp(token->data, "unset"))
		ft_unset(env_vars, token->next->data);
	// if (!ft_strcmp(token->data, "echo"))
	// 	ft_echo(token->next->data, int max_words);
	
	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
}
