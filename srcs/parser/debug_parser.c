/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:24:08 by minabe            #+#    #+#             */
/*   Updated: 2023/07/29 16:31:43 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(t_node *node)
{
	printf("ARGS: {\n");
	if (node->data == NULL)
		printf("data == NULL\n");
	else
	{
		for (size_t i = 0; node->data[i] != NULL; i++)
			printf("#%zu %s,\n", i, node->data[i]);
	}
	printf("}\n");
}

static void	print_redir(t_node *node)
{
	t_redirects	*current = node->redirects;
	printf("REDIR: {\n");
	if (current == NULL)
		printf("redir == NULL\n");
	else
	{
		for (size_t i = 0; current != NULL; i++, current = current->next)
			printf("#%zu filename: %s\n", i, current->filename);
	}
	printf("}\n");
}

static void	print_recursive(t_node *node)
{
	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_COMMAND)
	{
		print_args(node);
		print_redir(node);
	}
	printf("===LEFT===\n");
	print_recursive(node->left);
	printf("===RIGHT===\n");
	print_recursive(node->right);

}

void	debug_parser(t_node *node)
{
	printf("===========parse===========\n");
	print_recursive(node);
	printf("===========================\n");
}