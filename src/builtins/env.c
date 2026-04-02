/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 05:45:47 by user              #+#    #+#             */
/*   Updated: 2026/03/24 05:48:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	t_list	*current;

	current = shell->env;
	while (current)
	{
		ft_printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}
