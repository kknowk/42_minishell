/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/19 19:18:00 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	ft_select(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	t_env_var	*current;

	current = *env_vars;
	if (cmds[0] == NULL)
		return ;
	int j = 0;
	if (search_quot(cmds))
	{
		while (cmds[j])
		{
			cmds[j] = quot_handl(cmds[j], dir, env_vars);
			j++;
		}
	}
	else
	{
		while (cmds[j])
		{
			cmds[j] = doru_handl(cmds[j], dir, env_vars);
			j++;
		}
	}
	if (!cmds)
		return ;
	if (cmds[0][0] == '\0')
		return ;
	if (!ft_strcmp(cmds[0], "pwd"))
		dir->error = ft_pwd(dir);
	if (!ft_strcmp(cmds[0], "cd"))
		dir->error = ft_cd(dir, cmds[1], env_vars);
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit();
	if (!ft_strcmp(cmds[0], "env"))
		dir->error = ft_env(*env_vars);
	if (!ft_strcmp(cmds[0], "export"))
	{
		if (ft_export(env_vars, cmds[1]))
			exit(1);
		else
		{
			dir->error = 0;
			return ;
		}
	}
	if (!ft_strcmp(cmds[0], "unset"))
		dir->error = ft_unset(env_vars, cmds[1]);
	int	i = 0;
	while (cmds[i])
		i++;
	if (!ft_strcmp(cmds[0], "echo"))
		ft_echo(cmds, i - 1);
	else if (ft_strcmp(cmds[0], "cd") && ft_strcmp(cmds[0], "pwd") && ft_strcmp(cmds[0], "unset"))
	{
		if (access(cmds[0], X_OK) == 0)
		{
			if (fork() == 0)
			{
				execve(cmds[0], cmds, NULL);
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
			dir->error = execute_command(cmds[0], cmds) * 127;
	}
	// if (str)
	// 	free(str);
}

	
	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
