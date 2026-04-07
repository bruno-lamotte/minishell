/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_in_parent(t_shell *shell, unsigned char status)
{
	shell->exit_code = status;
	shell->should_exit = 1;
	return (shell->exit_code);
}

static void	exit_process(t_shell *shell, int status)
{
	cleanup_shell_exit(shell);
	exit(status);
}

static int	handle_numeric_exit_error(t_shell *shell, char *arg)
{
	print_exit_numeric_error(shell, arg);
	if (getpid() == shell->pid)
	{
		shell->exit_code = 2;
		shell->should_exit = 1;
		return (2);
	}
	exit_process(shell, 2);
	return (2);
}

int	builtin_exit(t_shell *shell, char **args)
{
	unsigned char	status;

	if (shell->interactive)
		ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		if (getpid() == shell->pid)
			return (exit_in_parent(shell, shell->exit_code));
		exit_process(shell, shell->exit_code);
	}
	if (!parse_exit_value(args[1], &status))
		return (handle_numeric_exit_error(shell, args[1]));
	if (args[2])
	{
		print_shell_prefix(shell);
		ft_putendl_fd("exit: too many arguments", 2);
		shell->exit_code = 1;
		return (1);
	}
	if (getpid() == shell->pid)
		return (exit_in_parent(shell, status));
	exit_process(shell, status);
	return (status);
}
