/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:39 by minabe            #+#    #+#             */
/*   Updated: 2023/07/12 11:01:51 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_lexer(t_lexer lexer)
{
	lexer.is_quoted = false;
	lexer.status = -1;
	lexer.quote_type = '\0';
}

t_token	*lexer(char *str)
{
	size_t	i;
	size_t	j;
	t_token	*token;
	t_lexer lexer;

	init_lexer(lexer);
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && lexer.is_quoted == false)
			i++;
		j = 0;
		while ((str[i + j] != ' ' && !lexer.is_quoted) && (lexer.is_quoted && str[i+j] != lexer.quote_type) && str[i + j] != '\0')
		{
			if (lexer.is_quoted && lexer.quote_type == str[i + j])
				lexer.is_quoted = false;
			else if (!lexer.is_quoted)
			{
				lexer.is_quoted = true;
				lexer.quote_type = str[i + j];
			}
			j++;
		}
		tokenlistadd_back(token, ft_substr(str, i, j));
		i += j;
	}
	return (token);
}
