/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:58:34 by khorike           #+#    #+#             */
/*   Updated: 2023/07/19 14:12:52 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	close_wait(int pipefd[2], pid_t pid1, pid_t pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

static void	p1(t_node *node, t_directory *dir,
		t_env_var **env_vars, int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (node->left != NULL)
		handle_commands(node->left, dir, env_vars);
	exit(0);
}

static void	p2(t_node *node, t_directory *dir,
		t_env_var **env_vars, int pipefd[2])
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (node->right != NULL)
		handle_commands(node->right, dir, env_vars);
	exit(0);
}

void	handle_commands(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
	{
		pipe(pipefd);
		pid1 = fork();
		if (pid1 == 0)
			p1(node, dir, env_vars, pipefd);
		pid2 = fork();
		if (pid2 == 0)
			p2(node, dir, env_vars, pipefd);
		close_wait(pipefd, pid1, pid2);
	}
	else
		ft_select(node->data, dir, env_vars);
}
