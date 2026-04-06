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

static int	exec_subshell(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(execute(node->children[0], shell));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute(t_ast *node, t_shell *shell)
{
	int	ret;

	if (!node)
		return (0);
	if (node->type == COMMAND)
		ret = exec_command(node, shell);
	else if (node->type == PIPE)
		ret = exec_pipe(node, shell);
	else if (node->type == AND)
		ret = exec_and(node, shell);
	else if (node->type == OR)
		ret = exec_or(node, shell);
	else if (node->type == SEQUENCE)
		ret = exec_sequence(node, shell);
	else if (node->type == SUBSHELL)
		ret = exec_subshell(node, shell);
	else
		ret = 0;
	if (node->is_bang)
		return (!ret);
	return (ret);
}
