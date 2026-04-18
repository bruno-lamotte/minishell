/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:18:06 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 15:54:18 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_tmp_filename(void)
{
	static int	counter;
	char		*pid_str;
	char		*num_str;
	char		*name;
	char		*tmp;

	pid_str = ft_itoa(getpid());
	num_str = ft_itoa(counter++);
	if (!pid_str || !num_str)
		return (free(pid_str), free(num_str), NULL);
	tmp = ft_strjoin("/tmp/minishell_heredoc_", pid_str);
	free(pid_str);
	if (!tmp)
		return (free(num_str), NULL);
	name = ft_strjoin(tmp, "_");
	free(tmp);
	if (!name)
		return (free(num_str), NULL);
	tmp = ft_strjoin(name, num_str);
	free(name);
	free(num_str);
	return (tmp);
}

int	heredoc_has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

char	*read_heredoc_line(t_shell *shell)
{
	if (shell->interactive)
		ft_putstr_fd("> ", STDERR_FILENO);
	return (read_plain_line());
}

int	write_heredoc_line(int fd, char *line, t_redirection *redir,
	t_shell *shell)
{
	char	*expanded;

	if (redir->expand_heredoc)
		expanded = expand_heredoc_line(line, shell);
	else
		expanded = ft_strdup(line);
	if (!expanded)
		return (0);
	ft_putendl_fd(expanded, fd);
	free(expanded);
	return (1);
}
