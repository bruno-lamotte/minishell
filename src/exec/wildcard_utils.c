/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:03:51 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 17:09:33 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LITERAL_STAR '\2'

int	is_dot_entry(char *name)
{
	return (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."));
}

int	match_pattern(char *pattern, char *name)
{
	if (!*pattern)
		return (!*name);
	if (*pattern == LITERAL_STAR)
		return (*name == '*' && match_pattern(pattern + 1, name + 1));
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*name)
		{
			if (match_pattern(pattern, name))
				return (1);
			name++;
		}
		return (match_pattern(pattern, name));
	}
	return (*pattern == *name && match_pattern(pattern + 1, name + 1));
}

int	split_pattern(char *pattern, char **dir, char **name)
{
	char	*slash;

	slash = ft_strrchr(pattern, '/');
	if (!slash)
	{
		*dir = ft_strdup(".");
		*name = ft_strdup(pattern);
	}
	else if (slash == pattern)
	{
		*dir = ft_strdup("/");
		*name = ft_strdup(slash + 1);
	}
	else
	{
		*dir = ft_substr(pattern, 0, slash - pattern);
		*name = ft_strdup(slash + 1);
	}
	return (*dir != NULL && *name != NULL);
}
