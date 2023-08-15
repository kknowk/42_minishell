/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/08/15 19:51:00 by minabe           ###   ########.fr       */
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

static void	switch_quote_state(t_lexer *lex, char c)
{
	if (lex->is_quoted == false && is_quote(c))
	{
		lex->is_quoted = true;
		lex->quote_type = c;
	}
	else if (lex->is_quoted == true && is_quote(c) && c == lex->quote_type)
	{
		lex->is_quoted = false;
		lex->quote_type = 0;
	}
}

static void	lexer_error(t_lexer *lex, char *str)
{
	t_token	*token;
	t_token	*tmp;

	printf("%s\n", str);
	token = lex->list_head;
	while (token != NULL)
	{
		tmp = token->next;
		free(token->data);
		free(token);
		token = tmp;
	}
}

static void	tokenize(t_lexer *lex, char *str, int *error, int *flag)
{
	size_t	start;
	char	c;

	start = lex->word_start;
	while (str[start + lex->word_len] != '\0')
	{
		c = str[start + lex->word_len];
		if (lex->word_len == 0 && (c == '|' || c == '<' || c == '>'))
		{
			lex->word_len += redirect_size(&str[start + lex->word_len]);
			break ;
		}
		else if (lex->is_quoted == false && (c == '|' || c == '<' || c == '>'))
			break ;
		switch_quote_state(lex, c);
		if (lex->is_quoted == false && is_whitespace(c))
			break ;
		lex->word_len++;
	}
	if (lex->is_quoted == true)
	{
		*error = QUOTED_ERROR;
		return ;
	}
	tokenlistadd_back(lex->token, ft_substr(str, start, lex->word_len), flag);
}

t_token	*lexer(char *str, int *error)
{
	t_lexer	lex;
	int		flag;

	flag = 0;
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
		tokenize(&lex, str, error, &flag);
		if (flag == 1)
		{
			lexer_error(&lex, PIPE_ERR1);
			*error = 2;
			return (NULL);
		}
		if (*error == QUOTED_ERROR)
		{
			lexer_error(&lex, NOT_CLOSE_QUOTED);
			return (NULL);
		}
		lex.word_start += lex.word_len;
	}
	return (lex.list_head);
}
