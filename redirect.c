/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/18 18:40:08 by minabe           ###   ########.fr       */
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

void	redirect(t_node *node, t_token **token)
{
	if (node->redirects == NULL)
		node->redirects = create_redirect();
	else
		puts("Todo");
	/* 現在は '<' '>' の場合のみ */
	node->redirects->filename = (*token)->next;
	/* 無効な入力は弾く機能を追加する */
	filefd = open_redir_file(node->redirects->filename->data);
	int	targetfd = 1;
	stashed_targetfd = stashfd(targetfd);
	if (filefd != targetfd)
	{
		dup2(filefd, targetfd);
		close(filefd);
	}
	// exec_command();
	dup2(stashed_targetfd, targetfd);
	// if ((*token)->type == '<' && (*token)->next->type == '<')
	// 	printf("D_LESSER\n");
}
