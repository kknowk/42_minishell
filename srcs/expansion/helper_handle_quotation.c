/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_handle_quotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:02:15 by khorike           #+#    #+#             */
/*   Updated: 2023/07/22 14:27:39 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	is_quoted(char *cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\'' || cmd[j] == '\"')
			return (true);
		j++;
	}
	return (false);
}

char	*search_quote(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (cmds[i][j] == '\'' || cmds[i][j] == '\"')
				return (cmds[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

int	get_var_length(const char *str)
{
	int	len;

	len = 1;
	while (str[len] != '\0' && str[len] != '\"'
		&& str[len] != '\'' && !isspace(str[len]))
		len++;
	return (len);
}

void	change_normal_pluss(t_parse_context *ctx, t_parse_state *state)
{
	*state = STATE_NORMAL;
	(ctx->i)++;
}
