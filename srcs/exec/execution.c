/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:07:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/22 16:55:47 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_commands(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(node, dir, env_vars);
	else
		ft_select(node->data, dir, env_vars); // ここの処理を一つ遅くしようかな。
}
