/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 09:37:28 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 09:06:42 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint_handler(int sig)
{
	g_signal = sig;
	write(STDERR_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	save_shell_terminal(t_shell *shell)
{
	shell->has_tty_state = 0;
	if (!shell->interactive)
		return ;
	rl_catch_signals = 0;
	rl_outstream = stderr;
	if (tcgetattr(STDIN_FILENO, &shell->tty_state) == 0)
		shell->has_tty_state = 1;
}

void	restore_shell_terminal(t_shell *shell)
{
	if (!shell->interactive || !shell->has_tty_state)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->tty_state);
}

void	cleanup_shell_terminal(t_shell *shell)
{
	if (!shell->interactive)
		return ;
	rl_free_line_state();
	rl_clear_history();
	rl_deprep_terminal();
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sa_int.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
