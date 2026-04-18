/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:10:10 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 17:10:50 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_assign_arg(t_list **env, char *arg)
{
	t_list	*node;
	char	*copy;
	t_list	*new_node;

	node = find_var(*env, arg);
	copy = ft_strdup(arg);
	if (!copy)
		return (0);
	if (node)
	{
		free(node->content);
		node->content = copy;
		return (1);
	}
	new_node = ft_lstnew(copy);
	if (!new_node)
		return (free(copy), 0);
	ft_lstadd_back(env, new_node);
	return (1);
}

int	env_unset_arg(t_list **env, char *arg)
{
	t_list	*node;
	t_list	*prev;

	prev = NULL;
	node = *env;
	while (node)
	{
		if (find_var(node, arg) == node)
		{
			if (prev)
				prev->next = node->next;
			else
				*env = node->next;
			ft_lstdelone(node, free_string);
			return (1);
		}
		prev = node;
		node = node->next;
	}
	return (1);
}

t_list	*env_dup_list(t_list *env)
{
	t_list	*copy;
	t_list	*new_node;
	char	*new_str;

	copy = NULL;
	while (env)
	{
		new_str = ft_strdup((char *)env->content);
		if (!new_str)
			return (free_env_list(&copy), NULL);
		new_node = ft_lstnew(new_str);
		if (!new_node)
		{
			free(new_str);
			return (free_env_list(&copy), NULL);
		}
		ft_lstadd_back(&copy, new_node);
		env = env->next;
	}
	return (copy);
}
