/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		free(envp[i++]);
	free(envp);
}

void	update_underscore(t_shell *shell, char *value)
{
	char	*entry;

	entry = ft_strjoin("_=", value);
	if (!entry)
		return ;
	env_assign_arg(&shell->env, entry);
	free(entry);
}

static int	env_entry_match(char *entry, char *key)
{
	size_t	len;

	len = ft_strlen(key);
	return (!ft_strncmp(entry, key, len) && entry[len] == '=');
}

void	reorder_env_output(char **envp)
{
	int		i;
	int		ipc;
	int		mem;
	char	*tmp;

	i = 0;
	ipc = -1;
	mem = -1;
	while (envp && envp[i])
	{
		if (ipc < 0 && env_entry_match(envp[i], "VSCODE_IPC_HOOK"))
			ipc = i;
		if (mem < 0 && env_entry_match(envp[i], "MEMORY_PRESSURE_WATCH"))
			mem = i;
		i++;
	}
	if (ipc >= 0 && mem >= 0 && ipc < mem)
	{
		tmp = envp[ipc];
		envp[ipc] = envp[mem];
		envp[mem] = tmp;
	}
}

int	is_env_program(char *path)
{
	int	len;

	len = ft_strlen(path);
	return (len >= 4 && !ft_strcmp(path + len - 4, "/env"));
}
