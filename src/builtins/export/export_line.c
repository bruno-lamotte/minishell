/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_line(char *entry)
{
	int	i;

	if (entry[0] == '_' && (entry[1] == '\0' || entry[1] == '='))
		return ;
	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (entry[i] && entry[i] != '=')
		i++;
	write(1, entry, i);
	if (entry[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		i++;
		while (entry[i])
		{
			if (entry[i] == '"' || entry[i] == '\\')
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(entry[i], 1);
			i++;
		}
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}
