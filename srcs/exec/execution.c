/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/08/04 17:10:39 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	t_redirects	*head;

	head = node->redirects;
	exec_redir(node->redirects, dir, env_vars);
	if (dir->error.flag)
	{
		dir->error.flag = 0;
		return ;
	}
	if (is_builtins(node->data[0]))
		exec_builtin(node->data, dir, env_vars);
	else
		exec_from_bin(node->data, dir, env_vars);
	return (restore_fd(head));
}

void	execution(t_node *node, t_directory *dir,
			t_env_var **env_vars)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(node, dir, env_vars);
	else
		exec_command(node, dir, env_vars);
}
