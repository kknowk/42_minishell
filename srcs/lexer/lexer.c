/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 16:44:42 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(t_lexer *lex, char *str)
{
	lex->str_len = ft_strlen(str);
	
	lex->is_quoted = false;
	lex->status = STATE_GENERAL;
	lex->quote_type = '\0';
	return (lex);
}

t_token	*lexer(char *str)
{
	size_t	i;
	t_token	*token;
	t_lexer lex;

	init_lexer(&lex, str);
	token = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		token = tokenlistadd_back(token, &str[i]);
		i++;
	}
	return (token);
}
