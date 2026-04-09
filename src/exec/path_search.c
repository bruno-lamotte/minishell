/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:38:26 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 14:14:58 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	if (!dir[0])
		return (ft_strdup(cmd));
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static int	path_status(char *path)
{
	struct stat	info;

	if (stat(path, &info) < 0)
		return (127);
	if (S_ISDIR(info.st_mode))
		return (126);
	if (access(path, X_OK) < 0)
		return (126);
	return (0);
}

char	*search_path(char **dirs, char *cmd, int *status)
{
	char	*path;
	char	**base;
	int		current;

	base = dirs;
	*status = 127;
	while (*dirs)
	{
		path = join_path(*dirs, cmd);
		if (!path)
			return (free_split(base), NULL);
		current = path_status(path);
		if (current == 0)
			return (*status = 0, free_split(base), path);
		if (current == 126)
			*status = 126;
		free(path);
		dirs++;
	}
	free_split(base);
	return (NULL);
}
