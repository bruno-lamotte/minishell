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

static void	skip_field_blanks(char *encoded, int *i)
{
	while (encoded[*i] == ' ' || encoded[*i] == '\t')
		(*i)++;
}

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

int	split_fields(char *encoded, int keep_empty, t_list **fields)
{
	int		i;
	int		start;
	char	*slice;

	i = 0;
	while (encoded[i])
	{
		skip_field_blanks(encoded, &i);
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

int	add_plain_field(t_list **plain_fields, char *plain)
{
	t_list	*node;

	node = ft_lstnew(plain);
	if (!node)
		return (free(plain), 0);
	ft_lstadd_back(plain_fields, node);
	return (1);
}
