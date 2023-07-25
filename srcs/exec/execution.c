/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/25 19:53:07 by minabe           ###   ########.fr       */
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
	while (node->redirects)
	{
		node->redirects->fd_file = open_redir_file(node->redirects);
		if (node->redirects->fd_file < 0)
			return ;
		printf("fd: %d\n", node->redirects->fd);
		printf("fd_file: %d\n", node->redirects->fd_file);
		printf("fd_backup: %d\n", node->redirects->fd_backup);
		do_redirect(node->redirects);
		node->redirects = node->redirects->next;
	}
	if (judgement_desuno(node->data, dir, env_vars) == 1)
		return ;
	if (dir->malloc_error == 1)
		exit(1);
	if (is_builtins(node->data[0]))
		return (select_builtin(node->data, dir, env_vars));
	return (exec_from_bin(node->data, dir));
}

void	execution(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(node, dir, env_vars);
	else
		exec_command(node, dir, env_vars);
}
