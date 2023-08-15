/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:13:54 by minabe            #+#    #+#             */
/*   Updated: 2023/08/15 19:10:08 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef enum e_tokentype
{
	CHAR_GENERAL = -1,
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_WHITESPACE = ' ',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_D_GREATER = -4,
	CHAR_D_LESSER,
	CHAR_IO_NUMBER,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*data;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

t_token	*tokenlistadd_back(t_token *token, char *data, int *flag);
void	tokenlist_clear(t_token *token);
t_token	*token_new(char *data);

bool	is_quote(char c);
bool	is_redirect(char c);
bool	is_whitespace(char c);

#endif