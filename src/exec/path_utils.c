/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:55:55 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 19:25:05 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path(char **dirs, char *cmd, int *status);

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

static char	*find_direct_path(char *cmd, int *status)
{
	*status = path_status(cmd);
	if (*status == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*find_path(char *cmd, t_shell *shell, int *status)
{
	char	**dirs;
	char	*env;

	if (!cmd[0] || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (*status = 127, NULL);
	if (ft_strchr(cmd, '/'))
		return (find_direct_path(cmd, status));
	env = get_env_val(shell, "PATH", 4);
	if (!env)
		return (find_direct_path(cmd, status));
	dirs = ft_split(env, ':');
	if (!dirs)
		return (NULL);
	return (search_path(dirs, cmd, status));
}
