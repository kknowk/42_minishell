/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/18 14:19:23 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(t_lexer *lex)
{
	t_token	*head;

	head = token_new(NULL);
	lex->word_start = 0;
	lex->word_len = 0;
	lex->is_quoted = false;
	lex->status = STATE_GENERAL;
	lex->quote_type = '\0';
	lex->token = head;
	lex->list_head = head;
	return (lex);
}

bool	is_special(char c)
{
	if (c == '\'' || c == '\"' || c == '|' || c == ' ' || c == '<' || c == '>')
		return (true);
	return (false);
}

void	tokenize(t_lexer *lex, char *str)
{
	if (lex->is_quoted)
	{
		while (str[lex->word_start + lex->word_len] != '\0')
		{
			lex->word_len++;
			if (str[lex->word_start + lex->word_len] == lex->quote_type)
			{
				lex->is_quoted = false;
				lex->quote_type = 0;
				lex->word_len++;
				tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, lex->word_len)); // substrの引数の型変更する必要あるかも?
				return ;
			}
		}
		tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, lex->word_len)); // substrの引数の型変更する必要あるかも?
	}
	else
	{
		if (!is_special(str[lex->word_start + lex->word_len]))
		{
			while (str[lex->word_start + lex->word_len] != '\0' && !is_special(str[lex->word_start + lex->word_len]))
				lex->word_len++;
			tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, lex->word_len)); // substrの引数の型変更する必要あるかも?
		}
		else
		{
			lex->word_len++;
			tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, 1)); // substrの引数の型変更する必要あるかも?
		}
	}
}

t_token	*lexer(char *str)
{
	t_lexer lex;

	init_lexer(&lex);
	lex.word_start = 0;
	while (str[lex.word_start] != '\0')
	{
		if (str[lex.word_start] == ' ')
		{
			lex.word_start++;
			continue ;
		}
		lex.word_len = 0;
		if (lex.is_quoted == false && (str[lex.word_start] == '\'' || str[lex.word_start] == '\"'))
		{
			lex.is_quoted = true;
			lex.quote_type = str[lex.word_start];
		}
		tokenize(&lex, str);
		lex.word_start += lex.word_len;
	}
	if(DEBUG)
		debug_lexer(&lex);
	return (lex.list_head);
}
