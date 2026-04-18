/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:53:41 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 12:59:43 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_key_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

t_list	*find_var(t_list *env, char *arg)
{
	int	len;

	len = env_key_len(arg);
	while (env)
	{
		if (!ft_strncmp((char *)env->content, arg, len)
			&& (((char *)env->content)[len] == '\0'
			|| ((char *)env->content)[len] == '='))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_val(t_shell *shell, char *name, int len)
{
	t_list	*node;
	char	*content;

	node = shell->env;
	while (node)
	{
		content = (char *)node->content;
		if (!ft_strncmp(content, name, len) && content[len] == '=')
			return (content + len + 1);
		node = node->next;
	}
	return (NULL);
}

static int	env_store_value(t_list **env, char *arg, t_list *node)
{
	char	*copy;
	t_list	*new_node;

	copy = ft_strdup(arg);
	if (!copy)
		return (0);
	if (node)
	{
		free(node->content);
		node->content = copy;
	}
	else
	{
		new_node = ft_lstnew(copy);
		if (!new_node)
			return (free(copy), 0);
		ft_lstadd_back(env, new_node);
	}
	return (1);
}

int	env_export_arg(t_list **env, char *arg)
{
	t_list	*node;
	t_list	*new_node;
	char	*copy;

	node = find_var(*env, arg);
	if (ft_strchr(arg, '='))
		return (env_store_value(env, arg, node));
	if (!node)
	{
		copy = ft_strdup(arg);
		if (!copy)
			return (0);
		new_node = ft_lstnew(copy);
		if (!new_node)
			return (free(copy), 0);
		ft_lstadd_back(env, new_node);
	}
	return (1);
}
