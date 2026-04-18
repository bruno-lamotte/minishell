/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:01:37 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 10:43:11 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	finish_heredoc(t_redirection *redir, t_shell *shell,
		char *tmp_name, int fd)
{
	close(fd);
	if (g_signal == SIGINT || !redir->delimiter)
		return (unlink(tmp_name), free(tmp_name), shell->exit_code = 130, 0);
	free(redir->file);
	redir->file = tmp_name;
	redir->unlink_after_use = 1;
	return (1);
}

static int	init_heredoc_file(t_redirection *redir, char **tmp_name, int *fd)
{
	*tmp_name = generate_tmp_filename();
	if (!*tmp_name)
		return (0);
	*fd = open(*tmp_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd < 0)
		return (free(*tmp_name), 0);
	redir->expand_heredoc = !heredoc_has_quotes(redir->file);
	free(redir->delimiter);
	redir->delimiter = dequote_string(redir->file);
	return (1);
}

static void	restore_heredoc_stdin(int saved_stdin)
{
	if (saved_stdin < 0)
		return ;
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

int	read_heredoc(t_redirection *redir, t_shell *shell)
{
	char	*tmp_name;
	char	*line;
	int		fd;
	int		saved_stdin;

	if (!init_heredoc_file(redir, &tmp_name, &fd))
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	setup_heredoc_signals();
	line = read_heredoc_line(shell);
	while (line && !g_signal && ft_strcmp(line, redir->delimiter))
	{
		if (!write_heredoc_line(fd, line, redir, shell))
			break ;
		free(line);
		line = read_heredoc_line(shell);
	}
	free(line);
	restore_heredoc_stdin(saved_stdin);
	restore_shell_terminal(shell);
	setup_signals();
	return (finish_heredoc(redir, shell, tmp_name, fd));
}

int	open_heredocs(t_parser *data, t_shell *shell)
{
	t_list			*current;
	t_redirection	*redir;

	current = data->here_docs;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (!read_heredoc(redir, shell))
			return (0);
		current = current->next;
	}
	return (1);
}
