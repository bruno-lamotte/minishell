/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:36:10 by marvin            #+#    #+#             */
/*   Updated: 2026/04/05 21:36:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_tmp_filename(void)
{
	int		i;
	char	*nbr;
	char	*name;

	i = 0;
	while (1)
	{
		nbr = ft_itoa(i);
		name = ft_strjoin("/tmp/.msh_heredoc_", nbr);
		free(nbr);
		if (access(name, F_OK) != 0)
			return (name);
		free(name);
		i++;
	}
}

void	read_loop(t_redirection *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->file))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	read_heredoc(t_redirection *redir)
{
	char	*tmp_file;
	int		fd;
	pid_t	pid;
	int		status;

	tmp_file = generate_tmp_filename();
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_loop(redir, fd);
		close(fd);
		exit(0);
	}
	close(fd);
	waitpid(pid, &status, 0);
	free(redir->file);
	redir->file = tmp_file;
	return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}

int	open_heredocs(t_parser *data)
{
	t_list			*current;
	t_redirection	*redir;

	current = data->here_docs;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (redir && redir->type == HEREDOC)
		{
			if (!read_heredoc(redir))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
