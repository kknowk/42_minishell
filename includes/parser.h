/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:13 by minabe            #+#    #+#             */
/*   Updated: 2023/07/29 15:01:30 by minabe           ###   ########.fr       */
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

typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND_OUTPUT,
	REDIRECT_HEREDOC,
}	t_redirect_type;

typedef struct s_redirects
{
	t_redirect_type		type;
	int					fd;
	int					fd_file;
	int					fd_backup;
	t_token				*filename;
	struct s_redirects	*prev;
	struct s_redirects	*next;
}	t_redirects;

typedef struct s_node
{
	t_nodetype		type;
	char			**data;
	t_redirects		*redirects;
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

t_node	*parser(t_token *token);
void		debug_parser(t_node *node);

void	destroy_parser(t_node *node);

void	set_redirect(t_node **node, t_token **token);
void	destroy_redirects(t_redirects *redirects);

#endif

// ex)

// echo aaa | ls | cat aaaa

// node->data[0] = '|'
// node->right->data = cat aaaa
// node->left->data[0] = '|'
// node->left->left->data = echo aaa
// node->left->right->data = ls
