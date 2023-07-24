/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/23 19:22:01 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# include <fcntl.h>

static t_redirects	*create_redirect(void)
{
	t_redirects	*redirect;

	redirect = malloc(sizeof(t_redirects));
	if (!redirect)
		exit(EXIT_FAILURE); // エラー処理する
	redirect->type = 0;
	redirect->filename = NULL;
	redirect->prev = NULL;
	redirect->next = NULL;
	return (redirect);
}

static t_redirect_type	judge_redir_type(t_token **token)
{
	if ((*token)->type == '<')
		return (REDIRECT_INPUT);
	else if ((*token)->type == '>')
		return (REDIRECT_OUTPUT);
	else if ((*token)->type == CHAR_D_GREATER)
		return (REDIRECT_APPEND_OUTPUT);
	else
		return (REDIRECT_HEREDOC);
}

void	redirect(t_node *node, t_token **token)
{
	if (node->redirects == NULL)
		node->redirects = create_redirect();
	else
		puts("ToDo");
	if ((*token)->next->type != CHAR_GENERAL)
	{
		puts("syntax error: ToDo");
		exit(EXIT_FAILURE); // エラー処理する
	}
	node->redirects->type = judge_redir_type(token);
	node->redirects->filename = (*token)->next;
	if ((*token)->next->type == CHAR_LESSER)
		node->redirects->fd = STDIN_FILENO;
	else if ((*token)->next->type == CHAR_GREATER)
		node->redirects->fd = STDOUT_FILENO;
	else if ((*token)->next->type == CHAR_D_LESSER)
		node->redirects->fd = STDOUT_FILENO;
}

void	destoroy_redirects(t_redirects *redirects)
{
	t_redirects	*tmp;

	while (redirects != NULL)
	{
		tmp = redirects->next;
		ft_free(redirects);
		redirects = tmp;
	}
}
