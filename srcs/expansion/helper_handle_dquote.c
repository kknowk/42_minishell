/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_handle_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:29:29 by khorike           #+#    #+#             */
/*   Updated: 2023/08/03 22:43:37 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	process_dollar(t_parse_context *ctx)
{
	int		var_length;
	char	*substring;
	char	*expanded;
	int		expanded_length;

	var_length = get_var_length(ctx->str + ctx->i);
	substring = ft_strndup(ctx->str + ctx->i, var_length);
	if (!substring)
		exit(EXIT_FAILURE);
	expanded = dollar_handle(substring, ctx->dir, ctx->env_vars);
	if (!expanded)
		exit(EXIT_FAILURE);
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
