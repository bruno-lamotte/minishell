/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:14:38 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 09:02:34 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	spawn_pipe_stage(t_ast *node, t_shell *shell, t_pipe_fds fds);
int		run_last_stage(t_ast *node, t_shell *shell, int in_fd);

static int	pipe_error(int in_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return (1);
}

static int	run_pipe_chain(t_ast *node, t_shell *shell, int in_fd)
{
	int			fd[2];
	int			ret;
	int			status;
	pid_t		pid;
	t_pipe_fds	fds;

	if (!node || node->type != PIPE)
		return (run_last_stage(node, shell, in_fd));
	if (pipe(fd) < 0)
		return (pipe_error(in_fd));
	fds.in_fd = in_fd;
	fds.out_fd = fd[1];
	fds.close_fd = fd[0];
	pid = spawn_pipe_stage(node->children[0], shell, fds);
	close(fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (pid < 0)
		return (close(fd[0]), pipe_error(STDIN_FILENO));
	ret = run_pipe_chain(node->children[1], shell, fd[0]);
	wait_for_pid(pid, &status);
	return (ret);
}

int	exec_pipe(t_ast *node, t_shell *shell)
{
	int	ret;

	prepare_foreground_job(shell);
	ret = run_pipe_chain(node, shell, STDIN_FILENO);
	finish_foreground_job(shell);
	return (ret);
}
