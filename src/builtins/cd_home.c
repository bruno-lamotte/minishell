/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:25:25 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 12:55:35 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static char	*read_file_content(char *path)
{
	char	c;
	char	*content;
	size_t	len;
	size_t	cap;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = NULL;
	len = 0;
	cap = 0;
	errno = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (!grow_line_buffer(&content, &cap, len + 2))
			return (close(fd), free(content), NULL);
		content[len++] = c;
	}
	close(fd);
	if (errno || !grow_line_buffer(&content, &cap, len + 1))
		return (free(content), NULL);
	return (content[len] = '\0', content);
}

static char	*get_uid_string(void)
{
	char	*content;
	char	*uid_line;
	int		start;
	int		end;

	content = read_file_content("/proc/self/status");
	if (!content)
		return (NULL);
	uid_line = ft_strnstr(content, "Uid:", ft_strlen(content));
	if (!uid_line)
		return (free(content), NULL);
	start = 4;
	while (uid_line[start] == ' ' || uid_line[start] == '\t')
		start++;
	end = start;
	while (ft_isdigit(uid_line[end]))
		end++;
	uid_line = ft_substr(uid_line, start, end - start);
	free(content);
	return (uid_line);
}

static char	*get_home_from_passwd(char *uid)
{
	char	**lines;
	char	**fields;
	char	*content;
	char	*home;
	int		i;

	content = read_file_content("/etc/passwd");
	lines = ft_split(content, '\n');
	free(content);
	home = NULL;
	i = 0;
	while (lines && lines[i] && !home)
	{
		fields = ft_split(lines[i], ':');
		if (fields && fields[2] && fields[5] && !ft_strcmp(fields[2], uid))
			home = ft_strdup(fields[5]);
		free_split(fields);
		i++;
	}
	free_split(lines);
	return (home);
}

char	*get_cd_home(t_shell *shell)
{
	char	*home;
	char	*uid;

	home = get_env_val(shell, "HOME", 4);
	if (home)
		return (ft_strdup(home));
	uid = get_uid_string();
	if (!uid)
		return (NULL);
	home = get_home_from_passwd(uid);
	free(uid);
	return (home);
}
