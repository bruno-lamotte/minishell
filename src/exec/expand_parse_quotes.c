/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

char	*expand_var_value(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
		return ((*i)++, ft_itoa(shell->exit_code));
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	name = ft_substr(str, start, *i - start);
	if (!name)
		return (NULL);
	value = get_env_val(shell, name, *i - start);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	handle_dquote_escape(t_encode_ctx *ctx)
{
	if (ctx->str[ctx->i] != '\\' || !ctx->str[ctx->i + 1])
		return (0);
	if (ctx->str[ctx->i + 1] != '$' && ctx->str[ctx->i + 1] != '"'
		&& ctx->str[ctx->i + 1] != '\\')
		return (0);
	if (!expand_buf_protected(&ctx->out, ctx->str[ctx->i + 1]))
		return (-1);
	ctx->i += 2;
	return (1);
}

static int	handle_dquote_var(t_encode_ctx *ctx)
{
	char	*value;

	if (ctx->str[ctx->i] != '$' || !ctx->str[ctx->i + 1])
		return (0);
	value = expand_var_value(ctx->str, &ctx->i, ctx->shell);
	if (!value || !expand_buf_string(&ctx->out, value, 1))
		return (free(value), -1);
	free(value);
	return (1);
}

int	parse_double_quote(t_encode_ctx *ctx)
{
	int	status;

	ctx->i++;
	while (ctx->str[ctx->i] && ctx->str[ctx->i] != '"')
	{
		status = handle_dquote_escape(ctx);
		if (status < 0)
			return (0);
		if (status > 0)
			continue ;
		status = handle_dquote_var(ctx);
		if (status < 0)
			return (0);
		if (status > 0)
			continue ;
		if (!expand_buf_protected(&ctx->out, ctx->str[ctx->i++]))
			return (0);
	}
	if (ctx->str[ctx->i] == '"')
		ctx->i++;
	return (1);
}

int	parse_single_quote(t_encode_ctx *ctx)
{
	ctx->i++;
	while (ctx->str[ctx->i] && ctx->str[ctx->i] != '\'')
	{
		if (!expand_buf_protected(&ctx->out, ctx->str[ctx->i++]))
			return (0);
	}
	if (ctx->str[ctx->i] == '\'')
		ctx->i++;
	return (1);
}
