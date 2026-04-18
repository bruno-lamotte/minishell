/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:35:35 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 09:05:25 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MASK_SQUOTE '\3'
#define MASK_DQUOTE '\4'
#define MASK_NEWLINE '\5'

void	copy_true_prefix(char *out, int *j);
int		handle_special_case(char *line, char *out, int *state, char quote);

static void	update_quote_state(char c, char *quote)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote && c == *quote)
		*quote = 0;
}

static void	handle_regular_char(char c, char *out, int *state, char quote)
{
	if (state[2] && (c == '<' || c == '>'))
	{
		copy_true_prefix(out, &state[1]);
		state[2] = 0;
	}
	else if (c != ' ' && c != '\t')
		state[2] = 0;
	if (quote == '\'' && c == '"')
		c = MASK_DQUOTE;
	else if (quote == '"' && c == '\'')
		c = MASK_SQUOTE;
	else if (quote && c == '\n')
		c = MASK_NEWLINE;
	out[state[1]++] = c;
}

char	*normalize_input_line(char *line)
{
	char	*out;
	int		state[3];
	char	quote;

	out = ft_calloc(ft_strlen(line) * 3 + 1, sizeof(char));
	if (!out)
		return (NULL);
	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	quote = 0;
	while (line[state[0]])
	{
		update_quote_state(line[state[0]], &quote);
		if (handle_special_case(line, out, state, quote))
			continue ;
		handle_regular_char(line[state[0]], out, state, quote);
		state[0]++;
	}
	return (out);
}
