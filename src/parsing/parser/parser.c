/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:25:07 by marvin            #+#    #+#             */
/*   Updated: 2026/03/17 05:39:25 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shift(t_list *stack, int state_id, t_token *token)
{
    t_stack *new_node;

    new_node = malloc(sizeof(t_stack));
    if (!new_node)
        return /*a completer*/;
    new_node->state_id = state_id;
    new_node->ast_node = NULL;
    new_node->symbol = ft_strdup(token->type);
    new_node->values = ft_strdup(token->value);
    if (!new_node->symbol || !new_node->values)
        return /*a completer*/;
    new_node->nb_values = 1;
    ft_lstadd_front(&stack, ft_lstnew(new_node));
}

int parser(t_parser *data, int **table)
{
    int     action;
    int     id;
    t_list  *stack;
    t_list *tokens_list;
    t_token token;

    stack = data->stack;
    tokens_list = data->tokens;
    while (tokens_list)
    {
        token = tokens_list->content;
        id = (t_stack *)(stack->content)->state_id;
        action = table[id][token];
        if (!action)
            return (print_parsing_error(data, table, id, token), 0);
        else if (action == ACCEPTED)
            return (1);
        else if (action < 0)
            reduce(data, stack, table, -action);
        else
        {
            shift(stack, action, token);
            tokens_list = tokens_list->next;
        }
    }
    return (0);
}
