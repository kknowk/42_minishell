/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/26 12:51:23 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

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
		free(token);
		token = tmp;
	}
	free(lex);
}

static void	tokenize(t_lexer *lex, char *str)
{
	size_t	start;
	char	c;

	start = lex->word_start;
	while (str[start + lex->word_len] != '\0')
	{
		c = str[start + lex->word_len];
		if (lex->word_len == 0 && (c == '|' || c == '<' || c == '>'))
		{
			if (is_redirect(c) && str[start + lex->word_len + 1] == c)
				lex->word_len += D_REDIR_SIZE;
			else
				lex->word_len++;
			break ;
		}
		else if (c == '|' || c == '<' || c == '>')
			break ;
		switch_quote_state(lex, c);
		if (is_whitespace(c) && lex->is_quoted == false)
			break ;
		lex->word_len++;
	}
	if (lex->is_quoted == true)
	{
		g_shell.dir.error = 2;
		lexer_error(lex, "minishell: syntax error: unexpected EOF");
		return ;
	}
	tokenlistadd_back(lex->token, ft_substr(str, start, lex->word_len));
}

t_token	*lexer(char *str)
{
	t_lexer	lex;

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
		tokenize(&lex, str);
		lex.word_start += lex.word_len;
	}
	if (DEBUG)
		debug_lexer(&lex);
	return (lex.list_head);
}
