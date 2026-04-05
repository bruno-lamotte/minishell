/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:10:45 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/05 11:22:33 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_builtin(char **args, t_shell *shell)
{
	if (!args || !args[0])
		return (-1);
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(args));
	if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(shell, args));
	if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(shell, args));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(shell, args));
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(shell));
	if (!ft_strcmp(args[0], "exit"))
		return (builtin_exit(shell, args));
	return (-1);
}

char	**env_to_arr(t_shell *shell)
{
	char	**arr;
	t_list	*cur;
	int		n;
	int		i;

	n = ft_lstsize(shell->env);
	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	cur = shell->env;
	i = 0;
	while (cur)
	{
		arr[i++] = ft_strdup((char *)cur->content);
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**dirs;
	char	*full;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_val(shell, "PATH", 4);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

void	exec_in_child(t_ast *node, t_shell *shell)
{
	char	**args;
	char	*path;
	char	**envp;
	int		ret;

	apply_redirections(node->redirections);
	if (!node->args || !node->args[0])
		exit(0);
	args = expand_args(node->args, shell);
	ret = run_builtin(args, shell);
	if (ret != -1)
		exit(ret);
	path = find_path(args[0], shell);
	envp = env_to_arr(shell);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", args[0]);
		exit(127);
	}
	execve(path, args, envp);
	perror(args[0]);
	exit(126);
}

static int	is_builtin(char *name)
{
	return (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"));
}

static void	restore_fds(int saved[3])
{
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	dup2(saved[2], STDERR_FILENO);
	close(saved[0]);
	close(saved[1]);
	close(saved[2]);
}

int	exec_command(t_ast *node, t_shell *shell)
{
	char	**args;
	int		ret;
	pid_t	pid;
	int		status;
	int		saved[3];

	if (!node->args || !node->args[0])
		return (0);
	args = expand_args(node->args, shell);
	if (is_builtin(args[0]))
	{
		saved[0] = dup(STDIN_FILENO);
		saved[1] = dup(STDOUT_FILENO);
		saved[2] = dup(STDERR_FILENO);
		if (node->redirections)
			apply_redirections(node->redirections);
		ret = run_builtin(args, shell);
		restore_fds(saved);
		return (ret);
	}
	pid = fork();
	if (pid == 0)
	{
		apply_redirections(node->redirections);
		execve(find_path(args[0], shell), args, env_to_arr(shell));
		ft_printf("minishell: %s: command not found\n", args[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
