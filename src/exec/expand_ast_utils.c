/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:22:34 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 18:46:02 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_ambiguous_words(char **words, int count)
{
	char	*joined;
	char	*tmp;
	int		i;

	if (count == 0)
		return (ft_strdup(""));
	joined = ft_strdup(words[0]);
	if (!joined)
		return (NULL);
	i = 1;
	while (i < count)
	{
		tmp = ft_strjoin(joined, " ");
		free(joined);
		if (!tmp)
			return (NULL);
		joined = ft_strjoin(tmp, words[i]);
		free(tmp);
		if (!joined)
			return (NULL);
		i++;
	}
	return (joined);
}

char	**expand_list_to_array(t_list **list, int count)
{
	char	**array;
	t_list	*tmp;
	int		i;

	array = ft_calloc(count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*list)
	{
		array[i++] = (char *)(*list)->content;
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	return (array);
}

int	append_expanded_words(t_list **words, char **expanded, int count)
{
	t_list	*node;
	int		i;

	i = 0;
	while (i < count)
	{
		node = ft_lstnew(expanded[i]);
		if (!node)
			return (0);
		ft_lstadd_back(words, node);
		i++;
	}
	free(expanded);
	return (1);
}

int	set_redirection_file(t_redirection *redir, char **expanded, int count)
{
	char	*value;

	if (count == 1)
	{
		free(redir->file);
		redir->file = expanded[0];
		free(expanded);
		return (1);
	}
	value = join_ambiguous_words(expanded, count);
	free_char_array(expanded, count);
	if (!value)
		return (0);
	free(redir->file);
	redir->file = value;
	redir->ambiguous = 1;
	return (1);
}
