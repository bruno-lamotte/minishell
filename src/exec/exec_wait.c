/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:48:36 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 19:24:48 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_foreground_job(t_shell *shell)
{
	if (shell->interactive)
		setup_wait_signals();
}

void	finish_foreground_job(t_shell *shell)
{
	if (shell->interactive)
		restore_shell_terminal(shell);
	setup_signals();
}

int	wait_for_pid(pid_t pid, int *status)
{
	while (waitpid(pid, status, 0) < 0)
	{
		if (errno == EINTR)
			continue ;
		return (0);
	}
	return (1);
}

int	wait_foreground_job(t_shell *shell, pid_t pid)
{
	int	status;

	prepare_foreground_job(shell);
	if (!wait_for_pid(pid, &status))
	{
		finish_foreground_job(shell);
		return (1);
	}
	finish_foreground_job(shell);
	return (wait_status_code(status));
}
