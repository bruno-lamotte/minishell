/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:51:27 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 16:33:21 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_input_line(t_shell *shell, char *line,
		int continued, int *done)
{
	char	*next;
	char	*joined;

	*done = 0;
	next = read_plain_line();
	if (!next)
	{
		*done = 1;
		return (line);
	}
	shell->input_line++;
	joined = join_input_lines(line, next, continued);
	free(line);
	free(next);
	return (joined);
}

char	*read_stdin_line(t_shell *shell)
{
	char	*line;
	int		continued;
	int		done;

	line = read_plain_line();
	if (line)
	{
		shell->input_line++;
		shell->command_line = shell->input_line;
	}
	while (line && (line_has_open_quote(line) || line_has_continuation(line)))
	{
		continued = line_has_continuation(line);
		if (continued)
			line[ft_strlen(line) - 1] = '\0';
		line = append_input_line(shell, line, continued, &done);
		if (!line)
			return (NULL);
		if (done)
			return (line);
	}
	return (line);
}
