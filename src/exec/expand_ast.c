/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:05:05 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/07 13:35:55 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_ambiguous_words(char **words, int count);
char	**expand_list_to_array(t_list **list, int count);
int		append_expanded_words(t_list **words, char **expanded, int count);
int		set_redirection_file(t_redirection *redir, char **expanded,
			int count);

static int	expand_args_array(t_ast *node, t_shell *shell)
{
	t_list	*words;
	char	**expanded;
	int		count;
	int		total;
	int		i;

	words = NULL;
	total = 0;
	i = 0;
	while (i < node->nb_args)
	{
		expanded = expand_word(node->args[i], shell, &count);
		if (!expanded || !append_expanded_words(&words, expanded, count))
			return (ft_lstclear(&words, free_string), 0);
		total += count;
		i++;
	}
	free_char_array(node->args, node->nb_args);
	node->args = expand_list_to_array(&words, total);
	node->nb_args = total;
	return (node->args != NULL);
}

static int	expand_redirections(t_ast *node, t_shell *shell)
{
	t_list			*current;
	t_redirection	*redir;
	char			**expanded;
	int				count;

	current = node->redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (redir->type != HEREDOC || !redir->unlink_after_use)
		{
			expanded = expand_word(redir->file, shell, &count);
			if (!expanded || !set_redirection_file(redir, expanded, count))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

void	expand_ast(t_ast *node, t_shell *shell)
{
	if (!node || node->type != COMMAND || node->expanded)
		return ;
	if (!expand_args_array(node, shell))
		return ;
	if (!expand_redirections(node, shell))
		return ;
	node->expanded = 1;
}
