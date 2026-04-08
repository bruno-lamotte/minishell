/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_saved_fds(int stdin_fd, int stdout_fd, int stderr_fd)
{
	if (stdin_fd >= 0)
		close(stdin_fd);
	if (stdout_fd >= 0)
		close(stdout_fd);
	if (stderr_fd >= 0)
		close(stderr_fd);
}

static int	with_redirections(t_list *redirections,
		int (*fn)(t_shell *, char **), t_shell *shell, char **args)
{
	int	saved_stdin;
	int	saved_stdout;
	int	saved_stderr;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0 || saved_stderr < 0)
	{
		close_saved_fds(saved_stdin, saved_stdout, saved_stderr);
		return (1);
	}
	if (!apply_redirections(redirections, shell))
		ret = 1;
	else if (fn)
		ret = fn(shell, args);
	else
		ret = 0;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close_saved_fds(saved_stdin, saved_stdout, saved_stderr);
	return (ret);
}

static int	exec_parent_builtin(t_ast *node, t_shell *shell)
{
	apply_assignments(shell, node);
	return (with_redirections(node->redirections, run_builtin, shell,
			node->args));
}

static int	command_status_in_parent(t_ast *node, t_shell *shell)
{
	t_shell	tmp;
	char	*path;
	int		status;

	tmp = *shell;
	tmp.env = env_dup_list(shell->env);
	if (!tmp.env && shell->env)
		return (1);
	apply_assignments(&tmp, node);
	path = find_path(node->args[0], &tmp, &status);
	if (!path)
	{
		print_command_error(&tmp, node->args[0], status);
		free_env_list(&tmp.env);
		return (status);
	}
	free(path);
	free_env_list(&tmp.env);
	return (0);
}

int	exec_command(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	expand_ast(node, shell);
	if (!node->args || !node->args[0])
	{
		apply_assignments(shell, node);
		return (with_redirections(node->redirections, NULL, shell, NULL));
	}
	if (is_env_fallback_builtin(shell, node->args))
		return (with_redirections(node->redirections, run_builtin, shell,
				node->args));
	if (is_builtin_command(node->args))
		return (exec_parent_builtin(node, shell));
	status = command_status_in_parent(node, shell);
	if (status)
		return (status);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		exec_in_child(node, shell);
	return (wait_foreground_job(shell, pid));
}
