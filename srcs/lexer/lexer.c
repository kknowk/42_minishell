/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/13 14:57:16 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(t_lexer *lex, char *str)
{
	t_token	*head;

	(void)str;
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
			printf("\n");
		lex->word_len = 0;
		while (str[lex->word_start + lex->word_len] != '\0')
		{
			if (str[lex->word_start + lex->word_len] == lex->quote_type)
			{
				lex->is_quoted = false;
				lex->quote_type = 0;
				lex->word_len++;
				// printf("%zu\n", lex->word_len);
				tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, lex->word_len));
				return ;
			}
			printf("\n");
			lex->word_len++;
		}
		tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, lex->word_len));
	}
	else
	{
		lex->word_len = 0;
		while (str[lex->word_start] == ' ')
			lex->word_start++;
		if (!is_special(str[lex->word_start + lex->word_len]))
		{
			while (str[lex->word_start + lex->word_len] != '\0' && str[lex->word_start + lex->word_len] != ' ')
				lex->word_len++;
			tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, lex->word_len)); // substrの引数の型変更する必要あるかも?
		}
		else
		{
			if ((str[lex->word_start + lex->word_len] == '<' && str[lex->word_start + lex->word_len + 1] == '<')
					|| (str[lex->word_start + lex->word_len] == '>' && str[lex->word_start + lex->word_len + 1] == '>'))
			{
				lex->word_len += 2;
				tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, 2));
			}
			// else if (str[lex->word_start + lex->word_len] == ' ')
			// {
			// 	lex->word_start++;
			// 	return ;
			// }
			else
			{
				lex->word_len++;
				tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, 1));
			}
		}
	}
}

t_token	*lexer(char *str)
{
	size_t	i;
	t_lexer lex;

	init_lexer(&lex, str);
	i = 0;
	while (str[i] != '\0')
	{
		if (lex.is_quoted == false && (str[i] == '\'' || str[i] == '\"'))
		{
			lex.is_quoted = true;
			lex.quote_type = str[i];
		}
		tokenize(&lex, str);
		i = lex.word_start + lex.word_len;
		lex.word_start = i;
	}
	return (lex.list_head);
}
