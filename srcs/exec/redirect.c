/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:36:17 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 20:55:59 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_file(t_redirects *redir)
{
	if (redir->type == REDIRECT_INPUT)
		redir->fd_file = open(redir->filename->data, O_RDONLY, 0);
	else if (redir->type == REDIRECT_OUTPUT)
		redir->fd_file = open(redir->filename->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		puts("ToDo");
	/* fdをdupする必要ある？ */
	return (redir->fd);
}

void	do_redirect(t_redirects *redirect)
{
	if (redirect->type == REDIRECT_INPUT || redirect->type == REDIRECT_OUTPUT)
	{
		redirect->fd = dup2(redirect->fd_backup, redirect->fd); // 
		return ;
	}
	// if (redirect->type == REDIRECT_APPEND_OUTPUT)
	// 	return (do_redirect_append_output(redirect));
	// if (redirect->type == REDIRECT_HEREDOC)
	// 	return (do_redirect_heredoc(redirect));
	else
	{
		puts("ToDo");
		return ;
	}
}

// void	close_redir_file(t_redirects *redirect)
// {
// 	;
// }
