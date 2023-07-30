/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:41:09 by minabe            #+#    #+#             */
/*   Updated: 2023/07/30 14:59:56 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*node_new(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(EXIT_FAILURE);
	node->type = NODE_COMMAND;
	node->data = NULL;
	node->redirects = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

static size_t	data_size(t_token *token)
{
	size_t	size;

	size = 0;
	if (token == NULL)
		return (size);
	while (token->type == CHAR_PIPE)
		token = token->next;
	while (token != NULL && token->type != CHAR_PIPE && \
			!is_redirect(token->type))
	{
		size++;
		token = token->next;
	}
	return (size);
}

int	store_data(t_node *node, t_token **token)
{
	size_t	i;
	size_t	size;

	size = data_size((*token));
	node->data = ft_calloc(size + 1, sizeof(char *));
	if (!node->data)
		exit(EXIT_FAILURE);
	i = 0;
	while ((*token) != NULL && (*token)->type != CHAR_PIPE)
	{
		if (is_redirect((*token)->type))
		{
			set_redirect(node, token);
			return (1);
		}
		else
			node->data[i] = ft_strdup((*token)->data);
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		else
			break ;
		i++;
	}
	return (0);
}

t_node	*parser(t_token *token)
{
	t_node	*node;
	t_node	*left;
	t_node	*right;
	t_token	*head;

	if (token == NULL)
		return (NULL);
	head = token;
	node = node_new();
	store_data(node, &token);
	while (token != NULL && token->type == CHAR_PIPE)
	{
		token = token->next;
		left = node;
		right = node_new();
		store_data(right, &token);
		node = node_new();
		node->type = NODE_PIPE;
		node->left = left;
		node->right = right;
	}
	tokenlist_clear(head);
	return (node);
}

void	destroy_parser(t_node *node)
{
	size_t	i;

	if (node == NULL)
		return ;
	if (node->left)
		destroy_parser(node->left);
	if (node->right)
		destroy_parser(node->right);
	if (node->data)
	{
		i = 0;
		while (node->data[i])
		{
			ft_free(node->data[i]);
			i++;
		}
		ft_free(node->data);
	}
	if (node->redirects)
		destroy_redirects(node->redirects);
	ft_free(node);
}
