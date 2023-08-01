/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/08/01 16:45:07 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtins(char *command)
{
	char	**commands;
	int		i;

	commands = ft_split("echo cd pwd export unset env exit", ' ');
	i = 0;
	while (commands[i])
	{
		if (ft_strlen(command) != ft_strlen(commands[i]))
		{
			ft_free(commands[i]);
			i++;
			continue ;
		}
		if (ft_strcmp(command, commands[i]) == 0)
		{
			while (commands[i])
				ft_free(commands[i++]);
			ft_free(commands);
			return (true);
		}
		ft_free(commands[i]);
		i++;
	}
	ft_free(commands);
	return (false);
}

void	exec_command(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	t_redirects	*head;

	head = node->redirects;
	exec_redir(node->redirects, dir, env_vars);
	if (is_builtins(node->data[0]))
		select_builtin(node->data, dir, env_vars);
	else
		exec_from_bin(node->data, dir);
	return (restore_fd(head));
}

void	execution(t_node *node, t_directory *dir,
			t_env_var **env_vars)
{
	if (node == NULL)
	{
		return ;
	}
	if (node->type == NODE_PIPE)
		exec_pipe(node, dir, env_vars);
	else
		exec_command(node, dir, env_vars);
}
