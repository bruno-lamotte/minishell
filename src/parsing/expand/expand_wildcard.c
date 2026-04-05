/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:51:29 by marvin            #+#    #+#             */
/*   Updated: 2026/04/05 22:51:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_matches(t_list **new_args, char **matches, int count, char *old_arg)
{
	int	i;

	if (matches && count > 0)
	{
		i = 0;
		while (i < count)
		{
			ft_lstadd_back(new_args, ft_lstnew(matches[i]));
			i++;
		}
		free(matches);
		free(old_arg);
	}
	else
		ft_lstadd_back(new_args, ft_lstnew(old_arg));
}

void	expand_wildcard_args(t_ast *node)
{
	t_list	*new_args;
	t_list	*tmp;
	char	**matches;
	int		count;
	int		i;

	new_args = NULL;
	i = 0;
	while (i < node->nb_args)
	{
		if (ft_strchr(node->args[i], '*'))
		{
			matches = get_wildcard_matches(node->args[i], &count);
			append_matches(&new_args, matches, count, node->args[i]);
		}
		else
			ft_lstadd_back(&new_args, ft_lstnew(node->args[i]));
		i++;
	}
	free(node->args);
	node->nb_args = ft_lstsize(new_args);
	node->args = malloc(sizeof(char *) * (node->nb_args + 1));
	i = 0;
	while (new_args)
	{
		node->args[i++] = (char *)new_args->content;
		tmp = new_args;
		new_args = new_args->next;
		free(tmp);
	}
	node->args[i] = NULL;
}
