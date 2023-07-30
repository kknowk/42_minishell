/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:58:34 by khorike           #+#    #+#             */
/*   Updated: 2023/07/30 11:48:31 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	close_wait(int pipefd[2], pid_t pid1, pid_t pid2)
{
	ft_close(pipefd[0]);
	ft_close(pipefd[1]);
	ft_waitpid(pid1, NULL, 0);
	ft_waitpid(pid2, NULL, 0);
}

static void	p1(t_node *node, t_directory *dir,
		t_env_var **env_vars, int pipefd[2])
{
	ft_close(pipefd[0]);
	ft_dup2(pipefd[1], STDOUT_FILENO);
	ft_close(pipefd[1]);
	if (node->left != NULL)
		execution(node->left, dir, env_vars);
	exit(0);
}

static void	p2(t_node *node, t_directory *dir,
		t_env_var **env_vars, int pipefd[2])
{
	ft_close(pipefd[1]);
	ft_dup2(pipefd[0], STDIN_FILENO);
	ft_close(pipefd[0]);
	if (node->right != NULL)
		execution(node->right, dir, env_vars);
	exit(0);
}

void	exec_pipe(t_node *node, t_directory *dir, t_env_var **env_vars)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	ft_pipe(pipefd);
	pid1 = ft_fork();
	if (pid1 == 0)
		p1(node, dir, env_vars, pipefd);
	pid2 = ft_fork();
	if (pid2 == 0)
		p2(node, dir, env_vars, pipefd);
	close_wait(pipefd, pid1, pid2);
}
