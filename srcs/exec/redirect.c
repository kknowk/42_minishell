/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:36:17 by minabe            #+#    #+#             */
/*   Updated: 2023/07/29 16:31:21 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_file(t_redirects *redir)
{
	if (redir->type == REDIRECT_INPUT)
	{
		printf("filename: %s\n", redir->filename);
		return (open(redir->filename, O_RDONLY));
	}
	else if (redir->type == REDIRECT_OUTPUT)
	{
		printf("filename: %s\n", redir->filename);
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	}
	else if (redir->type == REDIRECT_APPEND_OUTPUT)
	{
		puts("APPEND");
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
	}
	puts("HEREDOC: ToDo");
	return (-1);
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
	if (redirect->type == REDIRECT_HEREDOC)
		puts("ToDo");
	// 	return (do_redirect_heredoc(redirect));
	else
	{
		puts("ToDo");
		return ;
	}
}

void	restore_fd(t_redirects *redirect)
{
	if (redirect == NULL)
		return ;
	dup2(redirect->fd_backup, redirect->fd);
	close(redirect->fd_backup);
	redirect->fd_backup = -1;
}
