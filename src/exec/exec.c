/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <ynabti@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:25:43 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/05 17:55:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_and(t_ast *node, t_shell *shell)
{
	int	ret;

	ret = execute(node->children[0], shell);
	shell->exit_code = ret;
	if (ret == 0)
		return (execute(node->children[1], shell));
	return (ret);
}

static int	exec_or(t_ast *node, t_shell *shell)
{
	int	ret;

	ret = execute(node->children[0], shell);
	shell->exit_code = ret;
	if (ret != 0)
		return (execute(node->children[1], shell));
	return (ret);
}

static int	exec_sequence(t_ast *node, t_shell *shell)
{
	int	ret;

	ret = execute(node->children[0], shell);
	shell->exit_code = ret;
	return (execute(node->children[1], shell));
}

int	execute(t_ast *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == COMMAND)
		return (exec_command(node, shell));
	if (node->type == PIPE)
		return (exec_pipe(node, shell));
	if (node->type == AND)
		return (exec_and(node, shell));
	if (node->type == OR)
		return (exec_or(node, shell));
	if (node->type == SEQUENCE)
		return (exec_sequence(node, shell));
	return (0);
}
