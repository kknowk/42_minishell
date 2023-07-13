/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:13:54 by minabe            #+#    #+#             */
/*   Updated: 2023/07/13 16:54:51 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_token	t_token;

// \tや\0は無視??
typedef enum e_tokentype
{
	CHAR_GENERAL = -1,
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_WHITESPACE = ' ',
	CHAR_GREATER = '<',
	CHAR_LESSER = '>',
}	t_tokentype;

struct	s_token
{
	t_tokentype		type;
	char			*data;
	t_token			*prev;
	t_token			*next;
};

t_token	*tokenlistadd_back(t_token *token, char *data);
void	tokenlist_clear(t_token *token);
t_token	*token_new(char *data);

#endif