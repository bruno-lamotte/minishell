/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_redirection *redir)
{
	int		pfd[2];
	char	*line;

	if (pipe(pfd) == -1)
		return (0);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->file))
		{
			free(line);
			break ;
		}
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], "\n", 1);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

static int	apply_redir(t_redirection *redir)
{
	int	fd;

	if (redir->type == INPUT)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd < 0)
			return (perror(redir->file), 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == OUTPUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(redir->file), 0);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror(redir->file), 0);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (1);
}

int	apply_redirections(t_list *redirs)
{
	t_redirection	*redir;
	int				fd;

	while (redirs)
	{
		redir = (t_redirection *)redirs->content;
		if (redir->type == HEREDOC)
		{
			fd = handle_heredoc(redir);
			if (fd < 0)
				return (0);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (!apply_redir(redir))
			return (0);
		redirs = redirs->next;
	}
	return (1);
}
