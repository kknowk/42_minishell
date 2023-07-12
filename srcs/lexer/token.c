/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:23:15 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 14:05:06 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_tokentype(char *data)
{
	if (data[0] == '|')
		return (CHAR_PIPE);
	if (data[0] == '\'' && data[ft_strlen(data) - 1] == '\'')
		return (CHAR_QUOTE);
	if (data[0] == '\"' && data[ft_strlen(data) - 1] == '\"')
		return (CHAR_DQUOTE);
	if (data[0] == '<' && data[1] == '<')
		return (CHAR_DGREATER);
	if (data[0] == '<')
		return (CHAR_GREATER);
	if (data[0] == '>' && data[1] == '>')
		return (CHAR_DLESSER);
	if (data[0] == '>')
		return (CHAR_LESSER);
	else
		return (CHAR_GENERAL);
}

static t_token	*token_new(char *data)
{
	t_token	*new;

	/* strがNULLの場合ある?? */
	new = malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->data = data;
	new->next = NULL;
	new->type = check_tokentype(data);
	new->prev = NULL;
	return (new);
}

void	tokenlistadd_back(t_token *token, char *data)
{
	t_token	*new;

	new = token_new(data);
	if (token != NULL)
	{
		while (token->next != NULL)
			token = token->next;
		token->next = new;
		new->prev = token;
	}
	else
		token = new;
}

void	tokenlist_clear(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}
