/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static void	print_name_error(t_shell *shell, char *cmd, int status)
{
	char		*path;

	path = get_env_val(shell, "PATH", 4);
	if (status == 127 && (!path || !path[0]))
	{
		errno = ENOENT;
		print_shell_prefix(shell);
		perror(cmd);
		return ;
	}
	if (status != 127)
	{
		print_shell_prefix(shell);
		perror(cmd);
		return ;
	}
	print_shell_prefix(shell);
	print_command_name(cmd);
	ft_putendl_fd(": command not found", 2);
}

static void	print_path_error(t_shell *shell, char *cmd, int status)
{
	struct stat	info;

	if (status == 127)
		errno = ENOENT;
	else if (stat(cmd, &info) == 0 && S_ISDIR(info.st_mode))
		errno = EISDIR;
	else
		errno = EACCES;
	print_shell_prefix(shell);
	perror(cmd);
}

void	print_command_error(t_shell *shell, char *cmd, int status)
{
	if (!ft_strchr(cmd, '/'))
		return (print_name_error(shell, cmd, status));
	print_path_error(shell, cmd, status);
}

void	print_exec_error(t_shell *shell, char *cmd, int status)
{
	print_command_error(shell, cmd, status);
}
