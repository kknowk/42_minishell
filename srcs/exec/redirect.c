/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:36:17 by minabe            #+#    #+#             */
/*   Updated: 2023/07/29 19:24:54 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_file(t_redirects *redir)
{
	if (redir->type == REDIRECT_INPUT)
		return (open(redir->filename, O_RDONLY));
	if (redir->type == REDIRECT_OUTPUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	// if (redir->type == REDIRECT_APPEND_OUTPUT)
	return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

void	heredoc(t_redirects *redir)
{
	int		pipefd[2];
	char	*line;
	char	*tmp;
	char	*res = NULL;

	if (pipe(pipefd) == -1)
		puts("ToDo");
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
	dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
	ft_free(res);
}

void	do_redirect(t_redirects *redirect)
{
	if (redirect->type == REDIRECT_INPUT || redirect->type == REDIRECT_OUTPUT ||
		redirect->type == REDIRECT_APPEND_OUTPUT)
	{
		redirect->fd_backup = dup(redirect->fd);
		dup2(redirect->fd_file, redirect->fd);
		return ;
	}
	// if (redirect->type == REDIRECT_HEREDOC)
	return (heredoc(redirect));
}

void	restore_fd(t_redirects *redirect)
{
	if (redirect == NULL)
		return ;
	dup2(redirect->fd_backup, redirect->fd);
	close(redirect->fd_backup);
	redirect->fd_backup = -1;
}
