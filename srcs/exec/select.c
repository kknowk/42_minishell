/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:26:36 by khorike           #+#    #+#             */
/*   Updated: 2023/07/23 15:30:20 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	judgement_desuno(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int	j;

	if (cmds[0] == NULL)
		return (1);
	j = 0;
	while (cmds[j])
	{
		if (is_quoted(cmds[j]))
			cmds[j] = quote_handle(cmds[j], dir, env_vars);
		else
			cmds[j] = dollar_handle(cmds[j], dir, env_vars);
		j++;
	}
	if (!cmds)
		return (1);
	if (cmds[0][0] == '\0')
		return (1);
	return (0);
}

static int	sub(char **cmds, t_env_var **env_vars)
{
	if (ft_export(env_vars, cmds[1]))
		exit(1);
	else
		return (0);
}

int	exec_builtin(char **cmds, t_directory *dir, t_env_var **env_vars)
{
	int			i;

	i = 0;
	if (!ft_strcmp(cmds[0], "pwd"))
		return (ft_pwd(dir));
	if (!ft_strcmp(cmds[0], "cd"))
		return (ft_cd(dir, cmds[1], env_vars));
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit();
	if (!ft_strcmp(cmds[0], "env"))
		return (ft_env(*env_vars));
	if (!ft_strcmp(cmds[0], "export"))
		return (sub(cmds, env_vars));
	if (!ft_strcmp(cmds[0], "unset"))
		return (ft_unset(env_vars, cmds[1]));
	while (cmds[i])
		i++;
	// if (!ft_strcmp(cmds[0], "echo"))
	return (ft_echo(cmds, i - 1));
}

	// while (current)
	// {
	// 	t_env_var *next = current->next;
	// 	free(current->key);
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }
