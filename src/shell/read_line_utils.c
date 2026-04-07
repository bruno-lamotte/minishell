/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	grow_line_buffer(char **buf, size_t *cap, size_t len)
{
	char	*new_buf;
	size_t	new_cap;

	if (*cap > len)
		return (1);
	new_cap = *cap;
	if (!new_cap)
		new_cap = 32;
	while (new_cap <= len)
		new_cap *= 2;
	new_buf = malloc(new_cap);
	if (!new_buf)
		return (0);
	if (*buf)
	{
		ft_memcpy(new_buf, *buf, len);
		free(*buf);
	}
	*buf = new_buf;
	*cap = new_cap;
	return (1);
}

char	*read_plain_line(void)
{
	char	buffer;
	char	*line;
	size_t	len;
	size_t	cap;
	ssize_t	bytes;

	line = NULL;
	len = 0;
	cap = 0;
	bytes = read(STDIN_FILENO, &buffer, 1);
	while (bytes > 0)
	{
		if (buffer == '\n')
			break ;
		if (!grow_line_buffer(&line, &cap, len + 1))
			return (free(line), NULL);
		line[len++] = buffer;
		bytes = read(STDIN_FILENO, &buffer, 1);
	}
	if (bytes <= 0 && len == 0)
		return (free(line), NULL);
	if (!grow_line_buffer(&line, &cap, len + 1))
		return (free(line), NULL);
	line[len] = '\0';
	return (line);
}

int	line_has_open_quote(char *line)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (line && line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

int	line_has_continuation(char *line)
{
	int	len;
	int	count;

	len = ft_strlen(line);
	count = 0;
	while (len > 0 && line[len - 1] == '\\')
	{
		count++;
		len--;
	}
	return (count % 2 == 1);
}

char	*join_input_lines(char *line, char *next, int continued)
{
	char	*joined;
	char	*tmp;

	if (continued)
		return (ft_strjoin(line, next));
	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, next);
	free(tmp);
	return (joined);
}
