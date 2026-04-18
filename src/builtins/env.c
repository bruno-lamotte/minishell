/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:16:52 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 16:28:56 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	t_list	*node;

	env_assign_arg(&shell->env, "_=/usr/bin/env");
	node = shell->env;
	while (node)
	{
		if (env_has_value((char *)node->content))
			ft_putendl_fd((char *)node->content, 1);
		node = node->next;
	}
	return (0);
}
