/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:17:29 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 17:11:07 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_balanced_parentheses(char *line)
{
	char	quote;
	int		depth;
	int		i;

	quote = 0;
	depth = 0;
	i = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && line[i] == '(')
			depth++;
		else if (!quote && line[i] == ')')
		{
			if (depth == 0)
				return (0);
			depth--;
		}
		i++;
	}
	return (depth == 0);
}
