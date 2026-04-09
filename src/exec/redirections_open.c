/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_open.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:29:53 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 18:47:19 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MASK_STDERR '\6'

static int	print_redir_error(t_shell *shell, char *file)
{
	print_shell_prefix(shell);
	perror(file);
	return (0);
}

static int	open_input_redir(t_redirection *redir, t_shell *shell)
{
	char	*file;
	int		fd;
	int		target;

	file = redir->file;
	target = STDIN_FILENO;
	if (file && file[0] == MASK_STDERR)
	{
		file++;
		target = STDERR_FILENO;
	}
	else if (redir->fd)
		target = redir->fd;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_redir_error(shell, file));
	dup2(fd, target);
	close(fd);
	return (1);
}

static int	open_output_redir(t_redirection *redir, t_shell *shell)
{
	char	*file;
	int		flags;
	int		fd;
	int		target;

	flags = O_WRONLY | O_CREAT;
	if (redir->type == APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	file = redir->file;
	target = STDOUT_FILENO;
	if (file && file[0] == MASK_STDERR)
	{
		file++;
		target = STDERR_FILENO;
	}
	else if (redir->fd)
		target = redir->fd;
	fd = open(file, flags, 0666);
	if (fd < 0)
		return (print_redir_error(shell, file));
	dup2(fd, target);
	close(fd);
	return (1);
}

static int	open_heredoc_redir(t_redirection *redir, t_shell *shell)
{
	char	*file;
	int		fd;
	int		target;

	file = redir->file;
	target = STDIN_FILENO;
	if (file && file[0] == MASK_STDERR)
	{
		file++;
		target = STDERR_FILENO;
	}
	else if (redir->fd)
		target = redir->fd;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_redir_error(shell, file));
	dup2(fd, target);
	close(fd);
	if (redir->unlink_after_use)
		unlink(file);
	return (1);
}

int	open_redirection(t_redirection *redir, t_shell *shell)
{
	if (redir->type == INPUT)
		return (open_input_redir(redir, shell));
	if (redir->type == OUTPUT || redir->type == APPEND)
		return (open_output_redir(redir, shell));
	return (open_heredoc_redir(redir, shell));
}
