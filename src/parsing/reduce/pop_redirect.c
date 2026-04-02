/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:50:40 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 07:22:22 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection_symbol(t_stack *stack)
{
    return (!ft_strcmp(stack->symbol, "redirect_list")
        || !ft_strcmp(stack->symbol, "io_redirect"));
}

t_list  *get_redirection_from_symbol(t_parser *data, t_stack *stack)
{
    int i;
    t_redirection *new_redir;
    t_list *list_redirs;

    
    list_redirs = NULL;
    i = 0;
    while (i < stack->nb_values)
    {
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (NULL/*JSP*/);
        new_redir->file = ft_strdup(stack->values[i + 1]);
        if (!ft_strcmp(stack->values[i], "<"))
            new_redir->type = INPUT;
        else if (!ft_strcmp(stack->values[i], ">"))
            new_redir->type = OUTPUT;
        else if (!ft_strcmp(stack->values[i], ">>"))
            new_redir->type = APPEND;
        else if (!ft_strcmp(stack->values[i], "<<"))
        {
            new_redir->type = HEREDOC;
            ft_lstadd_back(&data->here_docs, ft_lstnew(new_redir));
        }
        ft_lstadd_back(&list_redirs, ft_lstnew(new_redir));
        i+=2;
    }
    return (list_redirs);
}

t_list  *pop_redirections_from_stack(t_parser *data, int lookahead)
{
    t_list          *redirections;
    t_list          *new_redir;
    t_list          *stack;

    redirections = NULL;
    stack = data->stack;
    while (lookahead--)
    {
        if (((t_stack *)(stack->content))->ast_node)
            ft_lstadd_back(&redirections, ((t_stack *)(stack->content))->ast_node->redirections);
        else if (is_redirection_symbol((t_stack *)(stack->content)))
        {
            new_redir = get_redirection_from_symbol(data, (t_stack *)(stack->content));
            if (!new_redir)
                return (NULL/*JSP*/);
            ft_lstadd_front(&redirections, new_redir);
        }
        stack = stack->next;
    }
    return (redirections);
}
