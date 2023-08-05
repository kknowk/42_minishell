/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:36:17 by minabe            #+#    #+#             */
/*   Updated: 2023/08/05 12:31:02 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_file(t_redirects *redir)
{
	if (redir->type == REDIRECT_INPUT)
		return (open(redir->filename, O_RDONLY, 0));
	if (redir->type == REDIRECT_OUTPUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

static void	heredoc(t_redirects *redir, int pipefd[2])
{
	char	*tmp;
	char	*line;
	char	*res;

	ft_pipe(pipefd);
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, redir->filename, ft_strlen(redir->filename)))
		{
			ft_free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		res = ft_strjoin(res, tmp);
		ft_free(tmp);
		ft_free(line);
	}
	ft_putstr_fd(pipefd[PIPE_WRITE], res);
	ft_free(res);
}

void	do_redirect(t_redirects *redirect)
{
	int		pipefd[2];

	if (redirect->type == REDIRECT_INPUT || redirect->type == REDIRECT_OUTPUT
		|| redirect->type == REDIRECT_APPEND_OUTPUT)
	{
		redirect->fd_backup = ft_dup(redirect->fd);
		ft_dup2(redirect->fd_file, redirect->fd);
		return ;
	}
	else
	{
		heredoc(redirect, pipefd);
		ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
		ft_close(pipefd[PIPE_READ]);
		ft_close(pipefd[PIPE_WRITE]);
	}
	return ;
}

int	exec_redir(t_redirects *redir, t_directory *dir, t_env_var **env_vars)
{
	while (redir != NULL)
	{
		redir->filename = expansion(redir->filename, dir, env_vars);
		if (redir->type != REDIRECT_HEREDOC)
		{
			redir->fd_file = open_redir_file(redir);
			if (redir->fd_file == -1)
			{
				dir->error.error_num = 1;
				return (FAILURE);
			}
		}
		do_redirect(redir);
		redir = redir->next;
	}
	return (SUCCESS);
}

void	restore_fd(t_redirects *redirect)
{
	if (redirect == NULL)
		return ;
	ft_dup2(redirect->fd_backup, redirect->fd);
	ft_close(redirect->fd_backup);
	redirect->fd_backup = -1;
}
