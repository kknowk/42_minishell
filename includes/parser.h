/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:13 by minabe            #+#    #+#             */
/*   Updated: 2023/07/16 20:54:33 by minabe           ###   ########.fr       */
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
	char				*direction;
	char				*filename;
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

#endif