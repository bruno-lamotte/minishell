/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_stage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:31:07 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 14:13:41 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipe_child(t_pipe_fds fds)
{
	if (fds.close_fd >= 0 && fds.close_fd != fds.in_fd
		&& fds.close_fd != fds.out_fd)
		close(fds.close_fd);
	if (fds.in_fd != STDIN_FILENO)
	{
		dup2(fds.in_fd, STDIN_FILENO);
		close(fds.in_fd);
	}
	if (fds.out_fd != STDOUT_FILENO)
	{
		dup2(fds.out_fd, STDOUT_FILENO);
		close(fds.out_fd);
	}
}

pid_t	spawn_pipe_stage(t_ast *node, t_shell *shell, t_pipe_fds fds)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipe_child(fds);
	if (node && node->type == COMMAND)
		exec_in_child(node, shell);
	exit_child_process(shell, NULL, execute(node, shell));
	return (0);
}

int	run_last_stage(t_ast *node, t_shell *shell, int in_fd)
{
	pid_t		pid;
	int			status;
	t_pipe_fds	fds;

	fds.in_fd = in_fd;
	fds.out_fd = STDOUT_FILENO;
	fds.close_fd = -1;
	pid = spawn_pipe_stage(node, shell, fds);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (pid < 0)
		return (1);
	if (!wait_for_pid(pid, &status))
		return (1);
	return (wait_status_code(status));
}
