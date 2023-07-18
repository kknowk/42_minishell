/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/18 20:36:40 by minabe           ###   ########.fr       */
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

static void	tokenize_quoted(t_lexer *lex, char *str)
{
	size_t	start;

	start = lex->word_start;
	while (str[start + lex->word_len] != '\0')
	{
		lex->word_len++;
		if (str[start + lex->word_len] == lex->quote_type)
		{
			lex->is_quoted = false;
			lex->quote_type = 0;
			lex->word_len++;
			tokenlistadd_back(lex->token, ft_substr(str, start, lex->word_len));
			return ;
		}
	}
	tokenlistadd_back(lex->token, ft_substr(str, start, lex->word_len));
}

static void	tokenize_general(t_lexer *lex, char *str)
{
	size_t	start;
	char	c;

	start = lex->word_start;
	c = str[start + lex->word_len];
	if (is_special(c))
	{
		if (is_redirect(c) && str[start + lex->word_len + 1] == c)
		{
			lex->word_len += D_REDIR_SIZE;
			tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, 2));
		}
		else
		{
			lex->word_len++;
			tokenlistadd_back(lex->token, ft_substr(str, lex->word_start, 1));
		}
	}
	else
	{
		while (str[start + lex->word_len] != '\0' && !is_special(str[start + lex->word_len]))
			lex->word_len++;
		tokenlistadd_back(lex->token, ft_substr(str, start, lex->word_len));
	}
}

void	tokenize(t_lexer *lex, char *str)
{
	if (lex->is_quoted == true)
		tokenize_quoted(lex, str);
	else
		tokenize_general(lex, str);
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
		if (lex.is_quoted == false && is_quote(str[lex.word_start]))
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
