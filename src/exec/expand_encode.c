/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:13:01 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 11:19:23 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static int	handle_special_prefix(t_encode_ctx *ctx)
{
	char	*home;
	int		status;

	if (ctx->i == 0 && ctx->str[ctx->i] == '~' && (!ctx->str[ctx->i + 1]
			|| ctx->str[ctx->i + 1] == '/'))
	{
		home = get_env_val(ctx->shell, "HOME", 4);
		if (home && !expand_buf_text(&ctx->out, home))
			return (-1);
		if (home)
			return (ctx->i++, ctx->keep_empty = 1, 1);
	}
	if (ctx->str[ctx->i] != '\\')
		return (0);
	status = (ctx->str[ctx->i + 1] != '\0');
	if (status && !expand_buf_protected(&ctx->out, ctx->str[ctx->i + 1]))
		return (-1);
	if (!status && !expand_buf_char(&ctx->out, ctx->str[ctx->i]))
		return (-1);
	ctx->i += 1 + status;
	ctx->keep_empty = 1;
	return (1);
}

static int	starts_quoted_segment(t_encode_ctx *ctx)
{
	return (ctx->str[ctx->i] == '\'' || ctx->str[ctx->i] == '"'
		|| (ctx->str[ctx->i] == '$' && (ctx->str[ctx->i + 1] == '"'
				|| ctx->str[ctx->i + 1] == '\'')));
}

static int	parse_quoted_segment(t_encode_ctx *ctx)
{
	int	had_quote_prefix;

	had_quote_prefix = 0;
	if (ctx->str[ctx->i] == '$')
	{
		ctx->i++;
		had_quote_prefix = 1;
	}
	ctx->keep_empty = 1;
	if (ctx->str[ctx->i] == '\'')
	{
		if (!parse_single_quote(ctx))
			return (0);
	}
	else
	{
		if (!parse_double_quote(ctx))
			return (0);
	}
	if (ctx->out.len > 0 || had_quote_prefix)
		ctx->keep_empty = 1;
	return (1);
}

static int	handle_quote_or_var(t_encode_ctx *ctx)
{
	char	*value;

	if (starts_quoted_segment(ctx))
		return (parse_quoted_segment(ctx));
	if (ctx->str[ctx->i] == '$' && ctx->str[ctx->i + 1])
	{
		value = expand_var_value(ctx->str, &ctx->i, ctx->shell);
		if (!value || !expand_buf_string(&ctx->out, value, 0))
			return (free(value), 0);
		free(value);
	}
	else if (!expand_buf_char(&ctx->out, ctx->str[ctx->i++]))
		return (0);
	if (ctx->out.len > 0)
		ctx->keep_empty = 1;
	return (1);
}

char	*encode_word(char *str, t_shell *shell, int *keep_empty)
{
	t_encode_ctx	ctx;
	int				status;

	ft_bzero(&ctx, sizeof(ctx));
	ctx.str = str;
	ctx.shell = shell;
	ctx.out.buf = ft_calloc(1, 1);
	if (!ctx.out.buf)
		return (NULL);
	ctx.out.cap = 1;
	while (ctx.str[ctx.i])
	{
		status = handle_special_prefix(&ctx);
		if (status < 0 || (status == 0 && !handle_quote_or_var(&ctx)))
			return (free(ctx.out.buf), NULL);
	}
	*keep_empty = ctx.keep_empty;
	return (ctx.out.buf);
}
