/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:41:09 by minabe            #+#    #+#             */
/*   Updated: 2023/07/15 17:33:02 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(EXIT_FAILURE);
	node->type = NODE_COMMAND;
	node->data = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

static size_t	data_size(t_token *token)
{
	size_t	size;

	size = 0;
	while (token->type == CHAR_PIPE)
		token = token->next;
	while (token != NULL && token->type != CHAR_PIPE)
	{
		size++;
		token = token->next;
	}
	return (size);
}



// tokenがNULLの場合ある？？
t_node	*parser(t_token *token)
{
	t_node	*node;
	// t_node	*left;
	// t_node	*right;
	size_t	i;
	size_t	size;

	node = init_node();
	while (token != NULL && token->type == CHAR_PIPE)
	{
		size = data_size(token);
		node->data = malloc(sizeof(char *) * size + 1);
		if (!node->data) // エラー処理
			exit(EXIT_FAILURE);
		i = 0;
		while (i <= size)
		{
			node->data[i] = token->data;
			token = token->next;
			i++;
		}
		token = token->next;
	}
	/* debug */
	// debug_parser(node);
	return (node);
}
