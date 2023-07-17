/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:37 by minabe            #+#    #+#             */
/*   Updated: 2023/07/17 18:47:40 by minabe           ###   ########.fr       */
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

void	redirect(t_node *node, t_token **token)
{
	node->redirects = create_redirect();
	/* リダイレクトのエラーも追加 */
	puts("redirect");
	if ((*token)->type == '<' && (*token)->next->type == '<')
		printf("D_LESSER\n");
	
}