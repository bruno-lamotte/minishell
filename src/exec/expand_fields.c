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

char	*encoded_slice(char *encoded, int start, int end)
{
	return (ft_substr(encoded, start, end - start));
}

int	add_field(t_list **fields, char *encoded)
{
	t_list	*node;

	node = ft_lstnew(encoded);
	if (!node)
		return (free(encoded), 0);
	ft_lstadd_back(fields, node);
	return (1);
}
