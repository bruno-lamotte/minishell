/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:39:03 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 12:57:09 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

int	grow_expand_buffer(t_expand_buf *buf, size_t need)
{
	char	*new_buf;
	size_t	new_cap;

	if (buf->cap >= need)
		return (1);
	new_cap = buf->cap;
	if (!new_cap)
		new_cap = 32;
	while (new_cap < need)
		new_cap *= 2;
	new_buf = malloc(new_cap);
	if (!new_buf)
		return (0);
	if (buf->buf)
	{
		ft_memcpy(new_buf, buf->buf, buf->cap);
		free(buf->buf);
	}
	buf->buf = new_buf;
	buf->cap = new_cap;
	return (1);
}

int	expand_buf_char(t_expand_buf *buf, char c)
{
	if (!grow_expand_buffer(buf, buf->len + 2))
		return (0);
	buf->buf[buf->len++] = c;
	buf->buf[buf->len] = '\0';
	return (1);
}

int	expand_buf_text(t_expand_buf *buf, char *text)
{
	size_t	text_len;

	text_len = ft_strlen(text);
	if (!grow_expand_buffer(buf, buf->len + text_len + 1))
		return (0);
	ft_memcpy(buf->buf + buf->len, text, text_len);
	buf->len += text_len;
	buf->buf[buf->len] = '\0';
	return (1);
}

int	expand_buf_protected(t_expand_buf *buf, char c)
{
	return (expand_buf_char(buf, PROTECTED_CHAR)
		&& expand_buf_char(buf, c));
}

int	expand_buf_string(t_expand_buf *buf, char *str, int protect)
{
	size_t	i;

	if (!str)
		return (1);
	if (!protect)
		return (expand_buf_text(buf, str));
	i = 0;
	while (str[i])
	{
		if (!expand_buf_protected(buf, str[i]))
			return (0);
		i++;
	}
	return (1);
}
