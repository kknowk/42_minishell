/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/17 13:34:16 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	ft_select(t_token *token, t_directory *dir, t_env_var **env_vars)
{
	t_env_var	*current;
	char		*str;

	current = *env_vars;
	if (token->data == NULL)
		return ;
	str = doru_handl(token->data, dir, env_vars);
	if (!str)
		return ;
	if (!ft_strcmp(str, "pwd"))
		dir->error = ft_pwd(dir);
	if (!ft_strcmp(str, "cd"))
		dir->error = ft_cd(dir, token->next->data);
	if (!ft_strcmp(str, "exit"))
		ft_exit();
	if (!ft_strcmp(str, "env"))
		dir->error = ft_env(*env_vars);
	if (!ft_strcmp(str, "export"))
	{
		if (ft_export(env_vars, token->next->data))
			exit(1);
		else
			dir->error = 0;
	}
	if (!ft_strcmp(str, "unset"))
		dir->error = ft_unset(env_vars, token->next->data);
	else if (ft_strcmp(str, "cd") && ft_strcmp(str, "pwd"))
	{
		if (access(str, X_OK) == 0)
		{
			if (fork() == 0)
			{
				execve(str, &str, NULL);
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
			dir->error = execute_command(str) * 127;
	}
	// if (str)
	// 	free(str);
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
