/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:06:41 by minabe            #+#    #+#             */
/*   Updated: 2023/07/15 14:22:58 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token(t_token *token)
{
	char	*type;

	type = NULL;
	printf("===========lexer===========\n");
	for (int i = 0; token != NULL; i++, token = token->next)
	{
		if (token->type == CHAR_PIPE)
			type = "PIPE";
		else if (token->type == CHAR_GREATER)
			type = "GREATER";
		else if (token->type == CHAR_LESSER)
			type = "LESSER";
		else if (token->type == CHAR_QUOTE)
			type = "CHAR_QUOTE";
		else if (token->type == CHAR_DQUOTE)
			type = " CHAR_DQUOTE";
		else if (token->type == CHAR_WHITESPACE)
			type = "CHAR_WHITESPACE";
		else
			type = "GENERAL";
		printf("#%d str: %s\t\tlen: %zu\t\ttype: %s\n", i, token->data, ft_strlen(token->data), type);
	}
	printf("===========================\n");
}

void	debug_lexer(t_lexer *lex)
{
	print_token(lex->token);
}
