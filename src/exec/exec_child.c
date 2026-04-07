/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp);
void	update_underscore(t_shell *shell, char *value);

void	exit_child_process(t_shell *shell, t_list **extra_env, int status)
{
	if (extra_env)
		free_env_list(extra_env);
	if (shell->current_line)
		free(shell->current_line);
	free_env_list(&shell->env);
	if (shell->parser)
		free_parser_data(shell->parser);
	else if (shell->ast)
		free_ast(shell->ast);
	rl_clear_history();
	exit(status);
}

static int	prepare_child(t_shell *tmp, t_shell *shell, t_ast *node)
{
	*tmp = *shell;
	tmp->interactive = 0;
	tmp->env = env_dup_list(shell->env);
	if (!tmp->env && shell->env)
		return (0);
	apply_assignments(tmp, node);
	if (!apply_redirections(node->redirections, shell))
		return (0);
	return (1);
}

static void	run_external(t_ast *node, t_shell *shell, t_shell *tmp)
{
	char	*path;
	char	**envp;
	int		status;

	path = find_path(node->args[0], tmp, &status);
	if (!path)
	{
		print_exec_error(tmp, node->args[0], status);
		exit_child_process(shell, &tmp->env, status);
	}
	update_underscore(tmp, path);
	envp = env_to_arr(tmp);
	if (!envp)
	{
		free(path);
		exit_child_process(shell, &tmp->env, 1);
	}
	if (is_env_program(path))
		reorder_env_output(envp);
	execve(path, node->args, envp);
	print_exec_error(tmp, node->args[0], 126);
	free(path);
	free_envp(envp);
	exit_child_process(shell, &tmp->env, 126);
}

void	exec_in_child(t_ast *node, t_shell *shell)
{
	t_shell	tmp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	expand_ast(node, shell);
	if (!prepare_child(&tmp, shell, node))
		exit_child_process(shell, &tmp.env, 1);
	if (!node->args || !node->args[0])
		exit_child_process(shell, &tmp.env, 0);
	if (is_env_fallback_builtin(&tmp, node->args))
		exit_child_process(shell, &tmp.env, run_builtin(&tmp, node->args));
	if (is_builtin_command(node->args))
	{
		exit_child_process(shell, &tmp.env, run_builtin(&tmp, node->args));
	}
	run_external(node, shell, &tmp);
}
