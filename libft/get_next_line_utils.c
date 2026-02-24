/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:18:16 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/29 22:18:18 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_size(t_global *lst)
{
	int	total;
	int	i;

	total = 0;
	while (lst)
	{
		i = 0;
		while (i < lst->siz)
		{
			if (lst->content[i] == '\n')
				return (total + 1);
			total++;
			i++;
		}
		lst = lst->next;
	}
	return (total);
}

int	is_eol(t_global *list)
{
	int			i;
	t_global	*tmp;

	tmp = list;
	while (tmp)
	{
		i = 0;
		while (i < tmp->siz)
		{
			if (tmp->content[i] == '\n')
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_clear(t_global **stash)
{
	t_global	*tmp;
	t_global	*next;

	if (!stash || !*stash)
		return ;
	tmp = *stash;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*stash = NULL;
}
