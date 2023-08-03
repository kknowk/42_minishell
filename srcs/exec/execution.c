/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/08/03 18:16:10 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	t_redirects	*head;

	head = node->redirects;
	exec_redir(node->redirects, dir, env_vars);
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
