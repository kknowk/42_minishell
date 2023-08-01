/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:24:08 by minabe            #+#    #+#             */
/*   Updated: 2023/08/01 18:17:11 by minabe           ###   ########.fr       */
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

static char	*judge_redir(t_redirects *redir)
{
	char	*type;

	if (redir->type == REDIRECT_INPUT)
		type = "REDIR_INPUT";
	else if (redir->type == REDIRECT_OUTPUT)
		type = "REDIR_OUTPUT";
	else if (redir->type == REDIRECT_APPEND_OUTPUT)
		type = "REDIR_APPEND";
	else if (redir->type == REDIRECT_HEREDOC)
		type = "REDIR_HEREDOC";
	else
		type = "UNKNOWN";
	return (type);
}

static void	print_redir(t_node *node)
{
	t_redirects	*redir = node->redirects;
	
	printf("REDIR: {\n");
	if (redir == NULL)
		printf("REDIR == NULL\n");
	else
	{
		for (size_t i = 0; redir; i++, redir = redir->next)
			printf("#%zu %s, %s,\n", i, judge_redir(redir), redir->filename);
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
	printf("{LEFT}\n");
	print_recursive(node->left);
	printf("{RIGHT}\n");
	print_recursive(node->right);

}

void	debug_parser(t_node *node)
{
	printf("===========parse===========\n");
	print_recursive(node);
	printf("===========================\n");
}