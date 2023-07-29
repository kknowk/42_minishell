/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:41:09 by minabe            #+#    #+#             */
/*   Updated: 2023/07/29 13:46:04 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*node_new(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
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
	while (token->type == CHAR_PIPE)
		token = token->next;
	while (token != NULL && token->type != CHAR_PIPE)
	{
		size++;
		token = token->next;
	}
	return (size);
}

void	store_data(t_node *node, t_token **token)
{
	size_t	i;
	size_t	size;

	size = data_size((*token));
	node->data = ft_calloc(size + 1, sizeof(char *));
	if (!node->data)
	{
		tokenlist_clear(*token);
		exit(EXIT_FAILURE); // 要検討
	}
	i = 0;
	while (i < size + 1 && (*token)->type != CHAR_PIPE)
	{
		node->data[i] = ft_strdup((*token)->data);
		if (is_redirect((*token)->type))
			set_redirect(node, token);
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		else
			break ;
		i++;
	}
}

t_node	*parser(t_token *token)
{
	t_node	*node;
	t_node	*left;
	t_node	*right;
	t_token	*tmp;

	if (token == NULL)
		return (NULL);
	tmp = token;
	node = node_new();
	if (node == NULL)
	{
		tokenlist_clear(token);
		exit(EXIT_FAILURE);
	}
	store_data(node, &token);
	while (token != NULL && token->type == CHAR_PIPE)
	{
		token = token->next;
		left = node;
		right = node_new();
		if (right == NULL)
		{
			tokenlist_clear(token);
			exit(EXIT_FAILURE);
		}
		store_data(right, &token);
		node = node_new();
		if (node == NULL)
		{
			tokenlist_clear(token);
			exit(EXIT_FAILURE);
		}
		node->type = NODE_PIPE;
		node->left = left;
		node->right = right;
	}
	if(DEBUG)
		debug_parser(node);
	tokenlist_clear(tmp);
	return (node);
}

void	free_strarray(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}

void	destroy_parser(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->left)
		destroy_parser(node->left);
	if (node->right)
		destroy_parser(node->right);
	if (node->data)
		free_strarray(node->data);
	if (node->redirects)
		destroy_redirects(node->redirects);
	ft_free(node);
}
