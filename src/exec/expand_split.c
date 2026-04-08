/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static int	next_field_end(char *encoded, int start)
{
	int	i;

	i = start;
	while (encoded[i])
	{
		if (encoded[i] == PROTECTED_CHAR && encoded[i + 1])
			i += 2;
		else if (encoded[i] == ' ' || encoded[i] == '\t')
			break ;
		else
			i++;
	}
	return (i);
}

static char	*encoded_slice(char *encoded, int start, int end)
{
	return (ft_substr(encoded, start, end - start));
}

static int	add_field(t_list **fields, char *encoded)
{
	t_list	*node;

	node = ft_lstnew(encoded);
	if (!node)
		return (free(encoded), 0);
	ft_lstadd_back(fields, node);
	return (1);
}

int	split_fields(char *encoded, int keep_empty, t_list **fields)
{
	int		i;
	int		start;
	char	*slice;

	i = 0;
	while (encoded[i])
	{
		while (encoded[i] == ' ' || encoded[i] == '\t')
			i++;
		if (!encoded[i])
			break ;
		start = i;
		i = next_field_end(encoded, start);
		slice = encoded_slice(encoded, start, i);
		if (!slice || !add_field(fields, slice))
			return (0);
	}
	if (!*fields && keep_empty)
		return (add_field(fields, ft_strdup("")));
	return (1);
}

char	**expand_fields_to_array(t_list **fields, int count)
{
	char	**array;
	int		i;
	t_list	*tmp;

	array = ft_calloc(count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*fields)
	{
		array[i++] = (char *)(*fields)->content;
		tmp = *fields;
		*fields = (*fields)->next;
		free(tmp);
	}
	array[i] = NULL;
	return (array);
}
