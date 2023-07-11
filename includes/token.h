/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:13:54 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 17:17:12 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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
	t_tokentype		type;
	char			*data;
	t_token			*prev;
	t_token			*next;
};

void	tokenlistadd_back(t_token *token, char *data);
void	tokenlist_clear(t_token *token);

#endif