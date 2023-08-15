/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:13 by minabe            #+#    #+#             */
/*   Updated: 2023/08/15 19:30:04 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define NO_FILENAME "minishell: syntax error near unexpected token `newline'\n"

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
	char				*filename;
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

t_node	*parser(t_token *token, int *error);
// void		debug_parser(t_node *node);

t_node	*destroy_parser(t_node *node);

int		set_redirect(t_node *node, t_token **token);
void	destroy_redirects(t_redirects *redirects);

#endif
