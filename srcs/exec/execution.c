/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 15:32:58 by minabe           ###   ########.fr       */
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
		if (ft_strcmp(command, commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	exec_command(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	// if (node->redirects)
	// 	open_redir_file(node->redirects);
	// while (node->redirects)
	// {
	// 	do_redirect(node->data);
	// 	node->redirects = node->redirects->next;
	// }
	if (is_builtins(node->data[0]))
		return (select_builtin(node->data, dir, env_vars));
	return ; // ここでexecveしたいんですが変更できませんか?
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
