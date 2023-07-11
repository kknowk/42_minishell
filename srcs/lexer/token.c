/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:23:15 by minabe            #+#    #+#             */
/*   Updated: 2023/07/11 15:55:37 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	token_new(char *data)
{
	t_token	*new;

	/* strがNULLの場合ある?? */
	new = malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->data = data;
	new->next = NULL;
	new->type = -1; // check関数導入!!
	new->prex = NULL;
	return (new);
}

void	tokenlistadd_back(t_token *token, char *data)
{
	t_token	*new;

	/* strがNULLの場合ある?? */
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

	while (token->next != NULL)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}
