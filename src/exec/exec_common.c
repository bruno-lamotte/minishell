/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_status_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	run_builtin(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(args));
	if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(shell, args));
	if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(shell));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(shell, args));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(shell, args));
	return (builtin_exit(shell, args));
}

int	is_builtin_command(char **args)
{
	if (!args || !args[0])
		return (0);
	if (!ft_strcmp(args[0], "echo") || !ft_strcmp(args[0], "cd")
		|| !ft_strcmp(args[0], "pwd") || !ft_strcmp(args[0], "export")
		|| !ft_strcmp(args[0], "unset") || !ft_strcmp(args[0], "exit"))
		return (1);
	return (0);
}

int	is_env_fallback_builtin(t_shell *shell, char **args)
{
	char	*path;

	if (!args || !args[0] || ft_strcmp(args[0], "env") || args[1])
		return (0);
	if (!shell->allow_env_fallback)
		return (0);
	path = get_env_val(shell, "PATH", 4);
	return (!path || !path[0]);
}

void	apply_assignments(t_shell *shell, t_ast *node)
{
	int	i;

	i = 0;
	while (i < node->nb_assignments)
	{
		env_assign_arg(&shell->env, node->assignments[i]);
		i++;
	}
}
