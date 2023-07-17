/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:13 by minabe            #+#    #+#             */
/*   Updated: 2023/07/17 15:10:25 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_nodetype
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_nodetype;

typedef struct s_redirects
{
	struct s_redirects	*prev;
	struct s_redirects	*next;
}	t_redirects;

typedef struct s_node
{
	t_nodetype		type;
	char			**data;
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

t_node	*parser(t_token *token);
void		debug_parser(t_node *node);

#endif

// ex)

// echo aaa | ls | cat aaaa

// node->data[0] = '|'
// node->right->data = cat aaaa
// node->left->data[0] = '|'
// node->left->left->data = echo aaa
// node->left->right->data = ls
