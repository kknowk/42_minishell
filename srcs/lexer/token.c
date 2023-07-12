/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:23:15 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 16:02:23 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokentype	judge_tokentype(char *data)
{
	if (data[0] == '|')
		return (CHAR_PIPE);
	if (data[0] == '\'' && data[ft_strlen(data) - 1] == '\'')
		return (CHAR_QUOTE);
	if (data[0] == '\"' && data[ft_strlen(data) - 1] == '\"')
		return (CHAR_DQUOTE);
	// if (data[0] == '<' && data[1] == '<')
	// 	return (CHAR_DGREATER);
	if (data[0] == '<')
		return (CHAR_GREATER);
	// if (data[0] == '>' && data[1] == '>')
	// 	return (CHAR_DLESSER);
	if (data[0] == '>')
		return (CHAR_LESSER);
	else
		return (CHAR_GENERAL);
}

t_token	*token_new(char *data)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->data = data;
	new->next = NULL;
	new->type = judge_tokentype(data);
	new->prev = NULL;
	return (new);
}

t_token *tokenlistadd_back(t_token *token, char *data)
{
	t_token	*new;
	t_token	*head;

	if (token == NULL)
		return (token_new(data));
	head = token;
	new = token_new(data);
	while (token->next != NULL)
		token = token->next;
	token->next = new;
	new->prev = token;
	return (head);
}

void	tokenlist_clear(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		puts("delete");
		tmp = token->next;
		free(token);
		token = tmp;
	}
}
