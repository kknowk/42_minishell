/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:24:12 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 17:57:32 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "token.h"

typedef enum e_token_state
{
	STATE_IN_QUOTED,
	STATE_IN_DQUOTED,
	STATE_GENERAL,
}	t_token_state;

typedef struct	s_lexer
{
	size_t			str_len;
	size_t			word_start;
	bool			is_quoted;
	char			quote_type;
	t_token			*token;
	t_token			*list_head;
	t_token_state	status;
}	t_lexer;

t_token	*lexer(char *str);

#endif