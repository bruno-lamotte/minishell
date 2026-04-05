/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:10:45 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/05 14:00:00 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static int	count_cmds(t_ast *node)
{
	if (!node || node->type != PIPE)
		return (1);
	return (count_cmds(node->children[0]) + count_cmds(node->children[1]));
}

static void	collect_cmds(t_ast *node, t_ast **cmds, int *idx)
{
	if (!node || node->type != PIPE)
	{
		cmds[(*idx)++] = node;
		return ;
	}
	collect_cmds(node->children[0], cmds, idx);
	collect_cmds(node->children[1], cmds, idx);
}

static int	**alloc_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

int	exec_pipe(t_ast *node, t_shell *shell)
{
	int		total;
	t_ast	**cmds;
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		status;
	int		idx;

	total = count_cmds(node);
	cmds = malloc(sizeof(t_ast *) * total);
	idx = 0;
	collect_cmds(node, cmds, &idx);
	pipes = alloc_pipes(total - 1);
	pids = malloc(sizeof(pid_t) * total);
	if (!cmds || !pipes || !pids)
		return (1);
	i = 0;
	while (i < total)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < total - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			close_pipes(pipes, total - 1);
			exec_in_child(cmds[i], shell);
		}
		i++;
	}
	close_pipes(pipes, total - 1);
	i = 0;
	while (i < total)
		waitpid(pids[i++], &status, 0);
	free(cmds);
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
