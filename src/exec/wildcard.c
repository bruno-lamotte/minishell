/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int		is_dot_entry(char *name);
int		match_pattern(char *pattern, char *name);
int		split_pattern(char *pattern, char **dir, char **name);
char	**sorted_matches(t_list **matches, int count);

static int	append_match(t_list **matches, char *dir, char *name)
{
	t_list	*node;
	char	*path;
	char	*tmp;

	if (!ft_strcmp(dir, "."))
		path = ft_strdup(name);
	else if (!ft_strcmp(dir, "/"))
		path = ft_strjoin(dir, name);
	else
	{
		tmp = ft_strjoin(dir, "/");
		if (!tmp)
			return (0);
		path = ft_strjoin(tmp, name);
		free(tmp);
	}
	if (!path)
		return (0);
	node = ft_lstnew(path);
	if (!node)
		return (free(path), 0);
	ft_lstadd_back(matches, node);
	return (1);
}

static int	collect_matches(DIR *dirp, char *dir, char *name, t_list **matches)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dirp);
	while (entry)
	{
		if (!is_dot_entry(entry->d_name)
			&& (name[0] == '.' || entry->d_name[0] != '.')
			&& match_pattern(name, entry->d_name)
			&& append_match(matches, dir, entry->d_name))
			count++;
		entry = readdir(dirp);
	}
	return (count);
}

char	**get_wildcard_matches(char *pattern, int *count)
{
	DIR				*dirp;
	t_list			*matches;
	char			*dir;
	char			*name;

	*count = 0;
	if (!split_pattern(pattern, &dir, &name))
		return (NULL);
	dirp = opendir(dir);
	if (!dirp)
		return (free(dir), free(name), NULL);
	matches = NULL;
	*count = collect_matches(dirp, dir, name, &matches);
	closedir(dirp);
	free(dir);
	free(name);
	if (!matches)
		return (NULL);
	return (sorted_matches(&matches, *count));
}
