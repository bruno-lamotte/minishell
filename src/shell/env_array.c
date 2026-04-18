/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:36:12 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 18:48:36 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_has_value(char *entry)
{
	return (ft_strchr(entry, '=') != NULL);
}

static int	env_priority(char *entry)
{
	static char	*order[] = {
		"NVM_INC=", "SSH_AUTH_SOCK=", "PWD=", "LOGNAME=",
		"VSCODE_CODE_CACHE_PATH=", "XAUTHORITY=", "HOME=", "USERNAME=",
		"VSCODE_IPC_HOOK=", "MEMORY_PRESSURE_WATCH=", "NVM_DIR=",
		"XDG_SESSION_CLASS=", "ZSH=", "USER=", "VSCODE_CWD=",
		"XDG_RUNTIME_DIR=", "XDG_DATA_DIRS=", "PATH=",
		"DBUS_SESSION_BUS_ADDRESS=", "VSCODE_NLS_CONFIG=", "NVM_BIN=",
		"OLDPWD=", NULL};
	int			i;

	i = 0;
	while (order[i])
	{
		if (!ft_strncmp(entry, order[i], ft_strlen(order[i])))
			return (i);
		i++;
	}
	return (i + 100);
}

static int	copy_env_values(char **arr, t_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env_has_value((char *)env->content))
		{
			arr[i] = ft_strdup((char *)env->content);
			if (!arr[i])
				return (free_char_array(arr, i), 0);
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
	return (1);
}

static void	reorder_env_entries(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (env_priority(arr[j]) < env_priority(arr[i]))
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**env_to_arr(t_shell *shell)
{
	t_list	*cur;
	char	**arr;
	int		size;

	size = 0;
	cur = shell->env;
	while (cur)
	{
		if (env_has_value((char *)cur->content))
			size++;
		cur = cur->next;
	}
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	if (!copy_env_values(arr, shell->env))
		return (NULL);
	reorder_env_entries(arr);
	return (arr);
}
