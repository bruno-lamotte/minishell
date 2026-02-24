/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:16:43 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/10 13:49:08 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_global	*add_node(t_global **stash, int fd)
{
	t_global	*new_node;
	t_global	*tmp;

	new_node = malloc(sizeof(t_global));
	if (!new_node)
		return (ft_clear(stash), NULL);
	new_node->siz = read(fd, new_node->content, BUFFER_SIZE);
	new_node->next = NULL;
	if (new_node->siz <= 0)
	{
		if (new_node->siz < 0)
			ft_clear(stash);
		free(new_node);
		return (NULL);
	}
	if (!*stash)
		*stash = new_node;
	else
	{
		tmp = *stash;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (new_node);
}

char	*extract_line(t_global *stash)
{
	int		i;
	int		j;
	int		len;
	char	*line;

	len = line_size(stash);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (stash)
	{
		i = 0;
		while (i < stash->siz)
		{
			line[j++] = stash->content[i];
			if (stash->content[i++] == '\n')
				break ;
		}
		if (j > 0 && line[j - 1] == '\n')
			break ;
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

void	clean_stash(t_global **stash)
{
	t_global	*last;
	t_global	*clean_node;
	int			i;
	int			j;

	clean_node = malloc(sizeof(t_global));
	if (!clean_node)
		return (ft_clear(stash));
	clean_node->next = NULL;
	last = *stash;
	while (last && last->next)
		last = last->next;
	i = 0;
	while (i < last->siz && last->content[i] != '\n')
		i++;
	if (i < last->siz && last->content[i] == '\n')
		i++;
	j = 0;
	while (i < last->siz)
		clean_node->content[j++] = last->content[i++];
	(1 && (clean_node->siz = j), (ft_clear(stash)));
	if (j > 0)
		*stash = clean_node;
	else
		free(clean_node);
}

void	gnl_clear(t_global **stash)
{
	int	i;

	i = 0;
	while (i < FD_MAX)
		ft_clear(&stash[i++]);
}

char	*get_next_line(int fd)
{
	static t_global	*stash[FD_MAX];
	char			*line;
	t_global		*node;

	if (fd == -1)
		return (gnl_clear(stash), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	while (!is_eol(stash[fd]))
	{
		node = add_node(&stash[fd], fd);
		if (!node && !stash[fd])
			return (NULL);
		if (!node)
			break ;
	}
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
		return (ft_clear(&stash[fd]), NULL);
	clean_stash(&stash[fd]);
	return (line);
}
/*
int	main(int ac, char *av[])
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	(void) ac;
	line = get_next_line(fd);
	while (line) {
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
	*/
