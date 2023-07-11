/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:24:12 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 15:18:05 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_token	t_token;

typedef enum e_tokentype
{
	CHAR_GENERAL,
	CHAR_QUOTE,
	CHAR_DQUOTE,
	CHAR_PIPE,
	CHAR_WHITESPACE,
	CHAR_GRATER,
	CHAR_LESSER,
}	t_tokentype;

typedef enum e_token_status
{
	IN_QUOTED,
	IN_DQUOTE,
	GENERAL,
}	t_token_status;

struct	s_token
{
	t_token_type	type;
	char			*data;
	t_token			*prev;
	t_token			*next;
};

typedef struct	s_lexer
{
	bool	is_quoted;
}	t_lexer;

int	lexer(char *line);

#endif