/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:13:54 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 14:29:43 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_token	t_token;

typedef enum e_tokentype
{
	CHAR_GENERAL,
	CHAR_QUOTE,
	CHAR_DQUOTE,
	CHAR_PIPE,
	CHAR_WHITESPACE,
	CHAR_GREATER,
	CHAR_LESSER,
	CHAR_DGREATER,
	CHAR_DLESSER,
}	t_tokentype;

struct	s_token
{
	t_tokentype		type;
	char			*data;
	t_token			*prev;
	t_token			*next;
};

void	tokenlistadd_back(t_token *token, char *data);
void	tokenlist_clear(t_token *token);

#endif