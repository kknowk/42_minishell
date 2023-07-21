/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:09:39 by khorike           #+#    #+#             */
/*   Updated: 2023/07/21 17:51:50 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	process_dquote_state(t_parse_context *ctx, t_parse_state *state)
{
	int		var_length;
	char	*substring;
	char	*expanded;
	int		expanded_length;

	if (ctx->str[ctx->i] == '\"')
		change_nomal_pluss(ctx, state);
	else if (ctx->str[ctx->i] == '$')
	{
		var_length = get_var_length(ctx->str + ctx->i);
		substring = ft_strndup(ctx->str + ctx->i, var_length);
		expanded = doru_handl(substring, ctx->dir, ctx->env_vars);
		expanded_length = ft_strlen(expanded);
		if (expanded_length < MAX_BUFFER_SIZE - ctx->j)
		{
			ft_strlcpy(ctx->result + ctx->j, expanded, expanded_length + 1);
			ctx->j += expanded_length;
			ctx->i += var_length;
		}
		free(expanded);
	}
	else
		ctx->result[(ctx->j)++] = ctx->str[(ctx->i)++];
	*state = STATE_NORMAL;
}

static t_parse_context	init_parse_context(char *str, t_directory *dir,
	t_env_var **env_vars)
{
	t_parse_context	ctx;

	ctx.str = str;
	ctx.i = 0;
	ctx.result = ft_calloc(MAX_BUFFER_SIZE, 1);
	ctx.j = 0;
	ctx.dir = dir;
	ctx.env_vars = env_vars;
	return (ctx);
}

static void	parse_and_append_char(t_parse_state *state, t_parse_context *ctx)
{
	if (ctx->str[ctx->i] == '\'')
	{
		ctx->i++;
		while (ctx->str[ctx->i] != '\'' && ctx->str[ctx->i] != '\0')
			ctx->result[ctx->j++] = ctx->str[ctx->i++];
		if (ctx->str[ctx->i] == '\'')
			ctx->i++;
	}
	else if (ctx->str[ctx->i] == '\"')
	{
		ctx->i++;
		*state = STATE_IN_DQUOTE;
	}
	else
		ctx->result[ctx->j++] = ctx->str[ctx->i++];
}

char	*quot_handl(char *str, t_directory *dir, t_env_var **env_vars)
{
	t_parse_context	ctx;
	t_parse_state	state;

	ctx = init_parse_context(str, dir, env_vars);
	if (!ctx.result)
		return (NULL);
	state = STATE_NORMAL;
	while (ctx.str[ctx.i] != '\0')
	{
		if (state == STATE_NORMAL)
			parse_and_append_char(&state, &ctx);
		else if (state == STATE_IN_DQUOTE)
			process_dquote_state(&ctx, &state);
	}
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}
