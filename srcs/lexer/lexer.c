/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 14:30:46 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(void)
{
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		exit(EXIT_FAILURE);
	lex->is_quoted = false;
	lex->status = GENERAL;
	lex->quote_type = '\0';
	return (lex);
}

t_token	*lexer(char *str)
{
	size_t	i;
	size_t	j;
	t_token	*token;
	t_lexer *lex;

	lex = init_lexer();
	token = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && lex->is_quoted == false)
			i++;
		j = 0;
		while ((str[i + j] != ' ' && !lex->is_quoted) && (lex->is_quoted && str[i+j] != lex->quote_type) && str[i + j] != '\0')
		{
			if (lex->is_quoted && lex->quote_type == str[i + j])
				lex->is_quoted = false;
			else if (!lex->is_quoted)
			{
				lex->is_quoted = true;
				lex->quote_type = str[i + j];
			}
			j++;
		}
		tokenlistadd_back(token, ft_substr(str, i, j));
		i += j;
	}
	free(lex);
	return (token);
}
