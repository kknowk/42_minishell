/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 18:10:01 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(t_lexer *lex, char *str)
{
	t_token	*head;

	head = token_new(NULL);
	lex->str_len = ft_strlen(str);
	lex->is_quoted = false;
	lex->status = STATE_GENERAL;
	lex->quote_type = '\0';
	lex->token = head;
	lex->list_head = head;
	return (lex);
}

t_token	*lexer(char *str)
{
	size_t	i;
	// size_t	j;
	t_lexer lex;

	init_lexer(&lex, str);
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		// j = 0;
		// while (str[i + j + 1] != )
		// lex.token = tokenlistadd_back(lex.token, ft_substr(str, i, j));
		i++;
		// i += j;
	}
	return (lex.list_head);
}
