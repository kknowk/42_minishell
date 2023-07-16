/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/16 16:14:55 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	ft_select(t_token *token, t_directory *dir, t_env_var **env_vars)
{
	t_env_var			*current;

	current = *env_vars;
	if (token->data == NULL)
		return ;
	if (!ft_strcmp(token->data, "pwd"))
		dir->error = ft_pwd(dir);
	if (!ft_strcmp(token->data, "cd"))
		dir->error = ft_cd(dir, token->next->data);
	if (!ft_strcmp(token->data, "exit"))
		ft_exit();
	if (!ft_strcmp(token->data, "env"))
		dir->error = ft_env(*env_vars);
	if (!ft_strcmp(token->data, "export"))
	{
		if (ft_export(env_vars, token->next->data))
			exit(1);
		else
			dir->error = 0;
	}
	if (!ft_strcmp(token->data, "unset"))
		dir->error = ft_unset(env_vars, token->next->data);
	if (!ft_strcmp(token->data, "$?"))
	{
		printf("%d\n", dir->error);
	}
	else if (ft_strcmp(token->data, "cd") && ft_strcmp(token->data, "pwd"))
	{
		if (access(token->data, X_OK) == 0)
		{
			if (fork() == 0)
			{
				execve(token->data, &token->data, NULL);
				perror("execve failed");
				exit(1);
			}
			else
			{
				wait(NULL);
				return ;
			}
		}
		else
			dir->error = execute_command(token->data);
	}
}

	// if (!ft_strcmp(token->data, "echo"))
	// 	ft_echo(toke->next->data, int max_words);
	
	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
