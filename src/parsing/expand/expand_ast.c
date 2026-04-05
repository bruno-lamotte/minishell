/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:39:15 by marvin            #+#    #+#             */
/*   Updated: 2026/04/05 21:39:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_redirections(t_list *redirs, t_shell *shell)
{
	t_list			*current;
	t_redirection	*redir;
	char			*tmp;

	current = redirs;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (redir && redir->type != HEREDOC)
		{
			tmp = redir->file;
			redir->file = expand_string(redir->file, shell);
			free(tmp);
		}
		current = current->next;
	}
}

void	expand_command_node(t_ast *node, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < node->nb_args)
	{
		tmp = node->args[i];
		node->args[i] = expand_string(node->args[i], shell);
		free(tmp);
	}
    expand_wildcards_args(node);
	i = -1;
	while (++i < node->nb_assignments)
	{
		tmp = node->assignments[i];
		node->assignments[i] = expand_string(node->assignments[i], shell);
		free(tmp);
	}
	expand_redirections(node->redirections, shell);
}

void	expand_ast(t_ast *node, t_shell *shell)
{
	int	i;

	if (!node)
		return ;
	if (node->type == COMMAND)
		expand_command_node(node, shell);
	i = 0;
	while (i < node->nb_children)
	{
		expand_ast(node->children[i], shell);
		i++;
	}
}
