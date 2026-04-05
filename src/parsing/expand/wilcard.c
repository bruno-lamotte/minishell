/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:50:39 by marvin            #+#    #+#             */
/*   Updated: 2026/04/05 22:50:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	match_pattern(char *str, char *pattern)
{
	if (!*pattern)
		return (!*str);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*str)
		{
			if (match_pattern(str, pattern))
				return (1);
			str++;
		}
		return (0);
	}
	if (*str && *str == *pattern)
		return (match_pattern(str + 1, pattern + 1));
	return (0);
}

void	insert_sorted(t_list **head, char *str)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*prev;

	new = ft_lstnew(ft_strdup(str));
	tmp = *head;
	prev = NULL;
	while (tmp && ft_strcmp((char *)tmp->content, str) < 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	new->next = tmp;
	if (prev)
		prev->next = new;
	else
		*head = new;
}

char	**get_wildcard_matches(char *pattern, int *count)
{
	DIR				*dir;
	struct dirent	*ent;
	t_list			*lst;
	t_list			*tmp;
	char			**arr;

	lst = NULL;
	*count = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((ent = readdir(dir)))
	{
		if (ent->d_name[0] != '.' || pattern[0] == '.')
		{
			if (match_pattern(ent->d_name, pattern))
			{
				insert_sorted(&lst, ent->d_name);
				(*count)++;
			}
		}
	}
	closedir(dir);
	if (!*count)
		return (NULL);
	arr = malloc(sizeof(char *) * (*count + 1));
	*count = 0;
	while (lst)
	{
		arr[(*count)++] = (char *)lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	arr[*count] = NULL;
	return (arr);
}
