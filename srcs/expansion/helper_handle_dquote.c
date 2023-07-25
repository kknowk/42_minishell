/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_handle_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:29:29 by khorike           #+#    #+#             */
/*   Updated: 2023/07/24 19:29:45 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	malloc_error(t_directory *dir)
{
	dir->malloc_error = 1;
	return ;
}

void	process_dollar(t_parse_context *ctx, t_directory *dir)
{
	int		var_length;
	char	*substring;
	char	*expanded;
	int		expanded_length;

	var_length = get_var_length(ctx->str + ctx->i);
	substring = ft_strndup(ctx->str + ctx->i, var_length);
	if (!substring)
		return (malloc_error(dir));
	expanded = dollar_handle(substring, ctx->dir, ctx->env_vars);
	expanded_length = ft_strlen(expanded);
	if (expanded_length < MAX_BUFFER_SIZE - ctx->j)
	{
		ft_strlcpy(ctx->result + ctx->j, expanded, expanded_length + 1);
		ctx->j += expanded_length;
		ctx->i += var_length;
	}
	ft_free(expanded);
}

void	process_normal_character(t_parse_context *ctx)
{
	ctx->result[(ctx->j)++] = ctx->str[(ctx->i)++];
}
