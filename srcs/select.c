/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/18 15:49:02 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	ft_select(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	t_env_var	*current;
	char		*str;
	char		*str1;

	current = *env_vars;
	if (cmds[0] == NULL)
		return ;
	str = doru_handl(cmds[0], dir, env_vars);
	if (cmds[1])
		str1 = doru_handl(cmds[1], dir, env_vars);
	if (!str || !str1)
		return ;
	if (!ft_strcmp(str, "pwd"))
		dir->error = ft_pwd(dir);
	if (!ft_strcmp(str, "cd"))
		dir->error = ft_cd(dir, cmds[1], env_vars);
	if (!ft_strcmp(str, "exit"))
		ft_exit();
	if (!ft_strcmp(str, "env"))
		dir->error = ft_env(*env_vars);
	if (!ft_strcmp(str, "export"))
	{
		if (ft_export(env_vars, str1))
			exit(1);
		else
		{
			dir->error = 0;
			return ;
		}
	}
	if (!ft_strcmp(str, "unset"))
		dir->error = ft_unset(env_vars, str1);
	int	i = 0;
	while (cmds[i])
		i++;
	if (!ft_strcmp(str, "echo"))
		ft_echo(cmds + 1, i - 1);
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

	
	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
