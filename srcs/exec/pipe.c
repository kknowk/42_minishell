/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:58:34 by khorike           #+#    #+#             */
/*   Updated: 2023/08/05 10:46:11 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	close_wait(int pipefd[2], pid_t pid1, pid_t pid2, t_directory *dir)
{
	int	status1;
	int	status2;

	ft_close(pipefd[PIPE_READ]);
	ft_close(pipefd[PIPE_WRITE]);
	ft_waitpid(pid1, &status1, 0);
	ft_waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
	{
		dir->error.error_num = WEXITSTATUS(status2);
	}
}

static void	p1(t_node *node, t_directory *dir,
		t_env_var **env_vars, int pipefd[2])
{
	ft_close(pipefd[PIPE_READ]);
	ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	ft_close(pipefd[PIPE_WRITE]);
	if (node->left != NULL)
		execution(node->left, dir, env_vars);
	exit(dir->error.error_num);
}

static void	p2(t_node *node, t_directory *dir,
		t_env_var **env_vars, int pipefd[2])
{
	ft_close(pipefd[PIPE_WRITE]);
	ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	ft_close(pipefd[PIPE_READ]);
	if (node->right != NULL)
		execution(node->right, dir, env_vars);
	exit(dir->error.error_num);
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
	close_wait(pipefd, pid1, pid2, dir);
}
