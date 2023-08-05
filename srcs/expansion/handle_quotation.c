/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:09:39 by khorike           #+#    #+#             */
/*   Updated: 2023/08/03 22:43:30 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	process_dquote_state(t_parse_context *ctx, t_parse_state *state)
{
	if (ctx->str[ctx->i] == '\"')
		change_normal_plus(ctx, state);
	else if (ctx->str[ctx->i] == '$' && ctx->str[ctx->i + 1] != '\"')
	{
		process_dollar(ctx);
	}
	else
	{
		process_normal_character(ctx);
	}
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

char	*quote_handle(char *str, t_directory *dir, t_env_var **env_vars)
{
	t_parse_context	ctx;
	t_parse_state	state;

	ctx = init_parse_context(str, dir, env_vars);
	if (!ctx.result)
		exit(EXIT_FAILURE);
	state = STATE_NORMAL;
	while (ctx.str[ctx.i] != '\0')
	{
		if (state == STATE_NORMAL)
			parse_and_append_char(&state, &ctx);
		else if (state == STATE_IN_DQUOTE)
			process_dquote_state(&ctx, &state);
	}
	ctx.result[ctx.j] = '\0';
	ft_free(ctx.str);
	return (ctx.result);
}
