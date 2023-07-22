/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/22 21:31:01 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_nodes(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(node, dir, env_vars);
	else
	{
		if (is_builtins(node->data[0]))
		{
			exec_builtin(node->data, dir, env_vars);
		}
	}
}
