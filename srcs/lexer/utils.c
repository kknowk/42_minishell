/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:52:19 by minabe            #+#    #+#             */
/*   Updated: 2023/07/18 18:56:29 by minabe           ###   ########.fr       */
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
	// if (c == ' ' || c == '\t')
	if (c == ' ')
		return (true);
	return (false);
}

bool	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}
