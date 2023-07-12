/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:24:12 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 14:29:47 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "token.h"

typedef enum e_token_status
{
	IN_QUOTED,
	IN_DQUOTED,
	GENERAL,
}	t_token_status;

typedef struct	s_lexer
{
	size_t			str_len;
	bool			is_quoted;
	char			quote_type;
	t_token_status	status;
}	t_lexer;

t_token	*lexer(char *str);

#endif