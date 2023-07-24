/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:36:17 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 19:31:13 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirect_input(t_redirects *redirect)
{
	puts("ToDo");
	(void)redirect;
}

static void	do_redirect_output(t_redirects *redirect)
{
	puts("ToDo");
	(void)redirect;
}

static void	do_redirect_append_output(t_redirects *redirect)
{
	puts("ToDo");
	(void)redirect;
}

static void	do_redirect_heredoc(t_redirects *redirect)
{
	puts("ToDo");
	(void)redirect;
}

void	do_redirect(t_redirects *redirect)
{
	if (redirect->type == REDIRECT_INPUT)
		return (do_redirect_input(redirect));
	if (redirect->type == REDIRECT_OUTPUT)
		return (do_redirect_output(redirect));
	if (redirect->type == REDIRECT_APPEND_OUTPUT)
		return (do_redirect_append_output(redirect));
	if (redirect->type == REDIRECT_HEREDOC)
		return (do_redirect_heredoc(redirect));
	else
	{
		puts("kokokuru??");
		return ;
	}
}

// void	close_redir_file(t_redirects *redirect)
// {
// 	;
// }
