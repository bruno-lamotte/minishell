/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:56:32 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 17:08:16 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static int	append_heredoc_part(t_expand_buf *buf, char *line, int *i,
		t_shell *shell)
{
	char	*value;

	if (line[*i] != '$' || !line[*i + 1])
		return (expand_buf_char(buf, line[(*i)++]));
	value = expand_var_value(line, i, shell);
	if (!value || !expand_buf_string(buf, value, 0))
		return (free(value), 0);
	free(value);
	return (1);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*encoded;
	char	*plain;
	int		keep_empty;

	keep_empty = 0;
	encoded = encode_word(str, shell, &keep_empty);
	if (!encoded)
		return (NULL);
	plain = strip_protected(encoded);
	free(encoded);
	return (plain);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	t_expand_buf	buf;
	int				i;

	ft_bzero(&buf, sizeof(buf));
	buf.buf = ft_calloc(1, 1);
	if (!buf.buf)
		return (NULL);
	buf.cap = 1;
	i = 0;
	while (line[i])
	{
		if (!append_heredoc_part(&buf, line, &i, shell))
			return (free(buf.buf), NULL);
	}
	return (buf.buf);
}

char	*dequote_string(char *str)
{
	t_expand_buf	buf;
	int				i;

	ft_bzero(&buf, sizeof(buf));
	buf.buf = ft_calloc(1, 1);
	if (!buf.buf)
		return (NULL);
	buf.cap = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else if (!expand_buf_char(&buf, str[i++]))
			return (free(buf.buf), NULL);
	}
	return (buf.buf);
}
