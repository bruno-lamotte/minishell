/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell_prefix(t_shell *shell)
{
	if (shell && !shell->interactive)
	{
		ft_putstr_fd("bash: line ", 2);
		ft_putnbr_fd(shell->command_line, 2);
		ft_putstr_fd(": ", 2);
	}
	else
		ft_putstr_fd("minishell: ", 2);
}

static void	print_escaped_char(char c)
{
	if (c == '\t')
		ft_putstr_fd("\\t", 2);
	else if (c == '\n')
		ft_putstr_fd("\\n", 2);
	else if (c == '\r')
		ft_putstr_fd("\\r", 2);
	else if (c == '\v')
		ft_putstr_fd("\\v", 2);
	else if (c == '\f')
		ft_putstr_fd("\\f", 2);
	else if (c == '\b')
		ft_putstr_fd("\\b", 2);
	else if (c == '\a')
		ft_putstr_fd("\\a", 2);
	else if (c == '\\' || c == '\'')
	{
		ft_putchar_fd('\\', 2);
		ft_putchar_fd(c, 2);
	}
	else
		ft_putchar_fd(c, 2);
}

void	print_command_name(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_isprint((unsigned char)cmd[i]))
		i++;
	if (!cmd[i])
	{
		ft_putstr_fd(cmd, 2);
		return ;
	}
	ft_putstr_fd("$'", 2);
	while (*cmd)
	{
		print_escaped_char(*cmd);
		cmd++;
	}
	ft_putchar_fd('\'', 2);
}

static int	use_command_not_found(t_shell *shell, int status)
{
	char	*path;

	path = get_env_val(shell, "PATH", 4);
	return (status == 127 && path && path[0]);
}

void	print_command_error(t_shell *shell, char *cmd, int status)
{
	struct stat	info;

	if (!ft_strchr(cmd, '/'))
	{
		if (use_command_not_found(shell, status))
		{
			print_shell_prefix(shell);
			print_command_name(cmd);
			ft_putendl_fd(": command not found", 2);
			return ;
		}
		errno = ENOENT;
		if (status != 127)
			errno = EACCES;
		return (print_shell_prefix(shell), perror(cmd));
	}
	if (status == 127)
		errno = ENOENT;
	else if (stat(cmd, &info) == 0 && S_ISDIR(info.st_mode))
		errno = EISDIR;
	else
		errno = EACCES;
	print_shell_prefix(shell);
	perror(cmd);
}
