/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_normalize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:52:04 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 14:16:32 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MASK_STDERR '\6'
#define MASK_BANG '\7'

void	copy_true_prefix(char *out, int *j)
{
	out[(*j)++] = 't';
	out[(*j)++] = 'r';
	out[(*j)++] = 'u';
	out[(*j)++] = 'e';
	out[(*j)++] = ' ';
}

static int	is_word_bang(char *line, int i)
{
	if (i > 0 && !is_blank(line[i - 1]) && !is_operator(line[i - 1]))
		return (1);
	if (line[i + 1] && !is_blank(line[i + 1]) && !is_operator(line[i + 1]))
		return (1);
	return (0);
}

static int	handle_fd_or_bang(char *line, char *out, int *state, char quote)
{
	if (!quote && line[state[0]] == '2' && line[state[0] + 1] == '>')
	{
		out[state[1]++] = '>';
		out[state[1]++] = MASK_STDERR;
		state[0] += 2;
		return (1);
	}
	if (!quote && line[state[0]] == '!' && is_word_bang(line, state[0]))
	{
		out[state[1]++] = MASK_BANG;
		state[0]++;
		return (1);
	}
	return (0);
}

static int	handle_pipe_or_overwrite(char *line, char *out,
		int *state, char quote)
{
	if (!quote && line[state[0]] == '|' && line[state[0] + 1] != '|')
	{
		out[state[1]++] = '|';
		state[2] = 1;
		state[0]++;
		return (1);
	}
	if (!quote && line[state[0]] == '>' && line[state[0] + 1] == '|'
		&& (state[0] == 0 || line[state[0] - 1] != '>'))
	{
		out[state[1]++] = '>';
		state[0] += 2;
		return (1);
	}
	return (0);
}

int	handle_special_case(char *line, char *out, int *state, char quote)
{
	if (handle_fd_or_bang(line, out, state, quote))
		return (1);
	return (handle_pipe_or_overwrite(line, out, state, quote));
}
