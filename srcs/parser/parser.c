/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:41:09 by minabe            #+#    #+#             */
/*   Updated: 2023/08/15 20:26:37 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	store_data(t_node *node, t_token **token);

t_node	*handle_pipe(t_token **token, t_node *node, int *error)
{
	t_node	*left;
	t_node	*right;

	left = node;
	if (*token == NULL)
	{
		printf(PIPE_ERR2);
		*error = 2;
		return (destroy_parser(node));
	}
	right = node_new();
	if (store_data(right, token) == FAILURE)
		return (destroy_parser(node));
	node = node_new();
	node->type = NODE_PIPE;
	node->right = right;
	node->left = left;
	return (node);
}

t_node	*parser(t_token *token, int *error)
{
	t_node	*node;
	t_token	*head;

	if (token == NULL)
		return (NULL);
	head = token;
	node = node_new();
	if (store_data(node, &token) == FAILURE)
		return (destroy_parser(node));
	while (token != NULL && token->type == CHAR_PIPE)
	{
		token = token->next;
		node = handle_pipe(&token, node, error);
		if (*error)
			return (NULL);
	}
	tokenlist_clear(head);
	return (node);
}

static int	store_data(t_node *node, t_token **token)
{
	size_t	i;

	node->data = ft_calloc(data_size((*token)) + 1, sizeof(char *));
	i = 0;
	while ((*token) != NULL && (*token)->type != CHAR_PIPE)
	{
		if (is_redirect((*token)->type))
		{
			if (set_redirect(node, token) == FAILURE)
			{
				printf(NO_FILENAME);
				return (FAILURE);
			}
			continue ;
		}
		else
			node->data[i] = ft_strdup((*token)->data);
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		else
			break ;
		i++;
	}
	return (SUCCESS);
}

t_node	*destroy_parser(t_node *node)
{
	size_t	i;

	if (node == NULL)
		return (NULL);
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
	return (NULL);
}
