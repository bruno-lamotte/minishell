/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fields.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

char	*strip_protected(char *encoded)
{
	char	*plain;
	size_t	i;
	size_t	j;

	plain = malloc(ft_strlen(encoded) + 1);
	if (!plain)
		return (NULL);
	i = 0;
	j = 0;
	while (encoded[i])
	{
		if (encoded[i] == PROTECTED_CHAR && encoded[i + 1])
			i++;
		plain[j++] = encoded[i++];
	}
	plain[j] = '\0';
	return (plain);
}

char	*wildcard_pattern(char *encoded)
{
	char	*plain;
	size_t	i;
	size_t	j;

	plain = malloc(ft_strlen(encoded) + 1);
	if (!plain)
		return (NULL);
	i = 0;
	j = 0;
	while (encoded[i])
	{
		if (encoded[i] == PROTECTED_CHAR && encoded[i + 1])
		{
			i++;
			if (encoded[i] == '*')
				plain[j++] = LITERAL_STAR;
			else
				plain[j++] = encoded[i++];
		}
		else
			plain[j++] = encoded[i++];
	}
	plain[j] = '\0';
	return (plain);
}

int	has_raw_wildcard(char *encoded)
{
	int	i;

	i = 0;
	while (encoded[i])
	{
		if (encoded[i] == PROTECTED_CHAR && encoded[i + 1])
			i += 2;
		else if (encoded[i++] == '*')
			return (1);
	}
	return (0);
}
