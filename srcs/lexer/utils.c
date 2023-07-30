/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:52:19 by minabe            #+#    #+#             */
/*   Updated: 2023/07/30 10:58:08 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

bool	is_redirect(char c)
{
	if (c == '<' || c == '>' || c == CHAR_D_GREATER || c == CHAR_D_LESSER)
		return (true);
	return (false);
}

size_t	redirect_size(char *str)
{
	size_t	size;

	if (is_redirect(str[0]) && str[1] == str[0])
		size = D_REDIR_SIZE;
	else
		size = S_REDIR_SIZE;
	return (size);
}
