/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/18 15:51:30 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirects	*create_redirect(void)
{
	t_redirects	*redirect;

	redirect = malloc(sizeof(t_redirects));
	redirect->type = 0;
	redirect->filename = NULL;
	redirect->prev = NULL;
	redirect->next = NULL;
	return (redirect);
}

static int	open_redir_file(char *filename)
{
	int filefd, stashed_targetfd;
	
	filefd = open(filename, O_R);
	return (filefd);
}

void	redirect(t_node *node, t_token **token)
{
	int stashed_targetfd;

	if (node->redirects == NULL)
		node->redirects = create_redirect();
	else
		puts("Todo");
	/* 現在は '<' '>' の場合のみ */
	node->redirects->filename = (*token)->next->data;
	/* 無効な入力は弾く機能を追加する */
	open_redir_file(node->redirects->filename);
	puts("redirect");
	if ((*token)->type == '<' && (*token)->next->type == '<')
		printf("D_LESSER\n");
	
}