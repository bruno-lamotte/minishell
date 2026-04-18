/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:50:40 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 07:22:22 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_symbol(t_stack *stack)
{
	return (!ft_strcmp(stack->symbol, "redirect_list")
		|| !ft_strcmp(stack->symbol, "io_redirect"));
}

static void	set_redirection_type(t_redirection *new_redir, char *symbol)
{
	if (!ft_strcmp(symbol, "<"))
		new_redir->type = INPUT;
	else if (!ft_strcmp(symbol, ">"))
		new_redir->type = OUTPUT;
	else if (!ft_strcmp(symbol, ">>"))
		new_redir->type = APPEND;
	else if (!ft_strcmp(symbol, "<<"))
		new_redir->type = HEREDOC;
}

static int	append_redirection(t_parser *data, t_list **redirs,
		t_redirection *new_redir)
{
	if (new_redir->type == HEREDOC)
		ft_lstadd_back(&data->here_docs, ft_lstnew(new_redir));
	ft_lstadd_back(redirs, ft_lstnew(new_redir));
	return (1);
}

t_list	*get_redirection_from_symbol(t_parser *data, t_stack *stack)
{
	int				i;
	t_redirection	*new_redir;
	t_list			*list_redirs;

	list_redirs = NULL;
	i = 0;
	while (i < stack->nb_values)
	{
		new_redir = ft_calloc(1, sizeof(t_redirection));
		if (!new_redir)
			return (NULL);
		new_redir->file = ft_strdup(stack->values[i + 1]);
		if (!new_redir->file)
			return (free(new_redir), NULL);
		set_redirection_type(new_redir, stack->values[i]);
		append_redirection(data, &list_redirs, new_redir);
		i += 2;
	}
	return (list_redirs);
}

t_list	*pop_redirections_from_stack(t_parser *data, int lookahead)
{
	t_list	*redirections;
	t_list	*new_redir;
	t_list	*stack;

	redirections = NULL;
	stack = data->stack;
	while (lookahead--)
	{
		if (((t_stack *)(stack->content))->ast_node)
		{
			ft_lstadd_back(&redirections,
				((t_stack *)(stack->content))->ast_node->redirections);
			((t_stack *)(stack->content))->ast_node->redirections = NULL;
		}
		else if (is_redirection_symbol((t_stack *)(stack->content)))
		{
			new_redir = get_redirection_from_symbol(data,
					(t_stack *)(stack->content));
			if (!new_redir)
				return (NULL);
			ft_lstadd_front(&redirections, new_redir);
		}
		stack = stack->next;
	}
	return (redirections);
}
