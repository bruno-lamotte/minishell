/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 23:31:59 by user              #+#    #+#             */
/*   Updated: 2026/04/02 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (!str[i])
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	nishere;

	i = 1;
	nishere = 0;
	if (!args[1])
	{
		ft_printf("\n");
		return (0);
	}
	while (args[i] && is_n_flag(args[i]))
	{
		nishere = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!nishere)
		ft_printf("\n");
	return (0);
}
