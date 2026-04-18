/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:32:44 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 12:56:52 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_unset_usage(void)
{
	ft_putendl_fd("unset: usage: unset [-f] [-v] [-n] [name ...]", 2);
}

static void	print_unset_option(t_shell *shell, char *arg)
{
	print_shell_prefix(shell);
	ft_putstr_fd("unset: -", 2);
	ft_putchar_fd(arg[1], 2);
	ft_putendl_fd(": invalid option", 2);
	print_unset_usage();
}

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1])
		{
			print_unset_option(shell, args[i]);
			return (2);
		}
		if (!ft_strcmp(args[i], "PATH"))
			shell->allow_env_fallback = 0;
		if (!env_unset_arg(&shell->env, args[i]))
			return (1);
		i++;
	}
	return (0);
}
