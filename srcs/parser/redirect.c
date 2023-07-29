/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/29 16:56:40 by minabe           ###   ########.fr       */
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
	redirect->fd = -1;
	redirect->fd_file = -1;
	redirect->fd_backup = -1;
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

// static t_redirects	*search_tail(t_redirects *lst)
// {
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

void	set_redirect(t_node *node, t_token **token)
{
	t_redirects	*new;

	puts("set_redir");
	new = create_redirect(); // malloc errorする？
	if ((*token)->next == NULL || (*token)->next->type != CHAR_GENERAL)
	{
		puts("syntax error: ToDo");
		exit(EXIT_FAILURE); // エラー処理する
	}
	new->type = judge_redir_type(token);
	new->filename = ft_strdup((*token)->next->data);
	if ((*token)->type == CHAR_LESSER)
		new->fd = STDIN_FILENO;
	else if ((*token)->type == CHAR_GREATER)
		new->fd = STDOUT_FILENO;
	else if ((*token)->type == CHAR_D_LESSER)
		new->fd = STDOUT_FILENO;
	if (node->redirects == NULL)
		node->redirects = new;
	else
	{
		puts("koko");
        while (node->redirects->next != NULL)
        {
			node->redirects = node->redirects->next;
        }
        node->redirects->next = new;
	}
	(*token) = (*token)->next;
}

void	destroy_redirects(t_redirects *redirects)
{
	t_redirects	*tmp;

	while (redirects != NULL)
	{
		tmp = redirects->next;
		ft_free(redirects);
		redirects = tmp;
	}
}
