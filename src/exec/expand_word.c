/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static int	add_plain_field(t_list **plain_fields, char *plain)
{
	t_list	*node;

	node = ft_lstnew(plain);
	if (!node)
		return (free(plain), 0);
	ft_lstadd_back(plain_fields, node);
	return (1);
}

static int	add_wildcard_matches(t_list **plain_fields, char **matches,
		int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!add_plain_field(plain_fields, matches[i]))
		{
			while (i < count)
				free(matches[i++]);
			free(matches);
			return (0);
		}
		i++;
	}
	free(matches);
	return (1);
}

static int	handle_matches(t_list **plain_fields, char *plain,
		char *encoded, int *count)
{
	char	*pattern;
	char	**matches;
	int		matches_count;

	if (!has_raw_wildcard(encoded))
		return ((*count)++, add_plain_field(plain_fields, plain));
	pattern = wildcard_pattern(encoded);
	if (!pattern)
		return (free(plain), 0);
	matches = get_wildcard_matches(pattern, &matches_count);
	free(pattern);
	if (matches_count > 0)
	{
		free(plain);
		*count += matches_count;
		return (add_wildcard_matches(plain_fields, matches, matches_count));
	}
	(*count)++;
	return (add_plain_field(plain_fields, plain));
}

static int	process_encoded_field(t_list **plain_fields, t_list *encoded_field,
		int *count)
{
	char	*plain;

	plain = strip_protected((char *)encoded_field->content);
	if (!plain)
		return (0);
	return (handle_matches(plain_fields, plain,
			(char *)encoded_field->content, count));
}

char	**expand_word(char *str, t_shell *shell, int *count)
{
	t_list	*encoded_fields;
	t_list	*plain_fields;
	t_list	*tmp;
	char	*encoded;
	int		keep_empty;

	encoded_fields = NULL;
	plain_fields = NULL;
	keep_empty = 0;
	*count = 0;
	encoded = encode_word(str, shell, &keep_empty);
	if (!encoded || !split_fields(encoded, keep_empty, &encoded_fields))
		return (free(encoded), NULL);
	free(encoded);
	while (encoded_fields)
	{
		if (!process_encoded_field(&plain_fields, encoded_fields, count))
			return (ft_lstclear(&encoded_fields, free_string),
				ft_lstclear(&plain_fields, free_string), NULL);
		free(encoded_fields->content);
		tmp = encoded_fields;
		encoded_fields = encoded_fields->next;
		free(tmp);
	}
	return (expand_fields_to_array(&plain_fields, *count));
}
