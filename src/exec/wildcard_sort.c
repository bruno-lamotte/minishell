/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**matches_to_array(t_list **matches, int count)
{
	char	**array;
	t_list	*next;
	int		i;

	array = ft_calloc(count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*matches)
	{
		array[i++] = (char *)(*matches)->content;
		next = (*matches)->next;
		free(*matches);
		*matches = next;
	}
	return (array);
}

static void	sort_match_array(char **array, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < count)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

char	**sorted_matches(t_list **matches, int count)
{
	char	**array;

	array = matches_to_array(matches, count);
	if (!array)
		return (NULL);
	sort_match_array(array, count);
	return (array);
}
