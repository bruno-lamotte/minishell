/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_env_copy(t_shell *shell, char *entry)
{
	t_list	*node;
	char	*value;

	value = ft_strdup(entry);
	node = ft_lstnew(value);
	if (!value || !node)
	{
		free(value);
		free(node);
		return (0);
	}
	ft_lstadd_back(&shell->env, node);
	return (1);
}

static void	update_shell_level(t_shell *shell)
{
	char	*value;
	char	*level_str;
	char	*entry;
	int		level;

	level = 1;
	value = get_env_val(shell, "SHLVL", 5);
	if (value)
		level = ft_atoi(value) + 1;
	level_str = ft_itoa(level);
	if (!level_str)
		return ;
	entry = ft_strjoin("SHLVL=", level_str);
	free(level_str);
	if (!entry)
		return ;
	env_assign_arg(&shell->env, entry);
	free(entry);
}

static void	update_shell_pwd(t_shell *shell)
{
	char	*cwd;
	char	*entry;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	tmp = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!tmp)
		return ;
	entry = tmp;
	env_assign_arg(&shell->env, entry);
	free(entry);
}

static void	ensure_oldpwd_var(t_shell *shell)
{
	if (!find_var(shell->env, "OLDPWD"))
		env_export_arg(&shell->env, "OLDPWD");
}

void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	ft_bzero(shell, sizeof(t_shell));
	shell->pid = getpid();
	shell->interactive = isatty(STDIN_FILENO);
	if (!shell->interactive)
		shell->input_line = 1;
	i = 0;
	while (envp[i])
	{
		if (!append_env_copy(shell, envp[i]))
			return ;
		i++;
	}
	shell->allow_env_fallback = (find_var(shell->env, "PATH") == NULL);
	update_shell_pwd(shell);
	ensure_oldpwd_var(shell);
	update_shell_level(shell);
}
