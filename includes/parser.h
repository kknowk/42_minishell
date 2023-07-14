/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:13 by minabe            #+#    #+#             */
/*   Updated: 2023/07/13 19:53:22 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_wordtype
{
	COMMAND,
	PIPE,
}	t_wordtype;

typedef struct s_tree
{
	t_wordtype		type;
	char			*data;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

#endif