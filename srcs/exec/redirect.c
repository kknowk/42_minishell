/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:36:17 by minabe            #+#    #+#             */
/*   Updated: 2023/07/25 15:32:52 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_file(t_redirects *redir)
{
	char	*filename;

	filename = redir->filename->data;
	if (redir->type == REDIRECT_INPUT)
	{
		puts("INPUT");
		return (open(filename, O_RDONLY));
	}
	else if (redir->type == REDIRECT_OUTPUT)
	{
		puts("OUTPUT");
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	}
	else if (redir->type == REDIRECT_APPEND_OUTPUT)
	{
		puts("APPEND");
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
	}
	puts("HEREDOC: ToDo");
	return (-1);
}

void	do_redirect(t_redirects *redirect)
{
	if (redirect->type == REDIRECT_INPUT || redirect->type == REDIRECT_OUTPUT)
	{
		redirect->fd_backup = redirect->fd;
		redirect->fd = dup(redirect->fd); // 
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
