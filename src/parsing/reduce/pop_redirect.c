/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:50:40 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/18 04:50:46 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection_symbol(t_stack *stack)
{
    return (!ft_strcmp(stack->symbol->type, "redirect_list")
        || !ft_strcmp(stack->symbol->type, "io_redirect"));
}

t_list  *get_redirection_from_symbol(t_stack *stack)
{
    int i;
    t_redirection *new_redir;
    t_list *list_redirs;

    
    list_redirs = malloc(sizeof(t_redirection));
    if (!list_redirs)
        return (NULL/*JSP*/);
    i = 0;
    while (i < stack->nb_values)
    {
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (NULL/*JSP*/);
        new_redir->file = ft_strdup(((t_stack *)(stack->content))->symbol);
        if (!ft_strcmp(stack->values[i], "<"))
            new_redir->type = INPUT;
        if (!ft_strcmp(stack->values[i], ">"))
            new_redir->type = OUTPUT;
        if (!ft_strcmp(stack->values[i], ">>"))
            new_redir->type = APPEND;
        if (!ft_strcmp(stack->values[i], "<<"))
            new_redir->type = HEREDOC;
        ft_lstadd_back(&list_redirs, ft_lstnew(new_redir));
        i++;
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
        else if (is_redirection_symbol(((t_stack *)(stack->content))->symbol))
        {
            new_redir = get_redirection_from_symbol((t_stack *)(stack->content));
            if (!new_redir)
                return (NULL/*JSP*/);
            ft_lstadd_front(&redirections, new_redirs);
        }
        stack = stack->next;
    }
    return (redirections);
}
