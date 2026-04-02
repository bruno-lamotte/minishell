/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:38:13 by user              #+#    #+#             */
/*   Updated: 2026/04/02 18:38:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *shell, char **args)
{
	long long	code;

	ft_printf("exit\n");
	if (!args[1])
		exit(shell->exit_code);
	if (!is_numeric(args[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit_code = 1;
		return (1);
	}
	code = ft_atoll(args[1]);
	exit((int)(code % 256));
}
