/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:45:50 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/18 05:05:55 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type get_node_type_from_rule(t_rule *rule)
{
    t_list *right_symbols;

    right_symbols = rule->right_symbols;
    if (ft_strnstr(rule->left_symbol, "cmd", ft_strlen(rule->left_symbol)))
        return (COMMAND);
    while (right_symbols)
    {
        if (!ft_strcmp(right_symbol->content, "subshell"))
            return (SUBSHELL);
        if (!ft_strcmp(right_symbol->content, "PIPE"))
            return (PIPE);
        if (!ft_strcmp(right_symbol->content, "SEMI"))
            return (SEQUENCE);
        if (!ft_strcmp(right_symbol->content, "AND_IF"))
            return (AND);
        if (!ft_strcmp(right_symbol->content, "OR_IF"))
            return (OR);
        right_symbols = right_symbols->next;
    }
    return (UNKNOWN);
}

t_rule  *get_rule_from_id(t_parser *data, int id)
{
    t_list *rules;

    rules = data->rules;
    while (rules)
    {
        if (((t_rule *)(rules->content))->id == id)
            return ((t_rule *)(rules->content));
        rules = rules->next;
    }
    return (NULL);
}

int is_node_already_type(t_parser *data, int lookahead, t_node_type node_type)
{
    t_list *stack;

    stack = data->stack;
    while (lookahead--)
        stack = stack->next;
    return ((t_stack *)(stack->content)->ast_node->type == node_type);
}

void    free_char_array(char **array, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void    clear_stack_after_reduce(t_parser *data, int nb_items, int should_free_ast)
{
    t_list *stack;

    while (nb_items--)
    {
        stack = data->stack;
        data->stack = stack->next;
        if (should_free_ast)
        {
            if ((t_stack *)(stack->content)->ast_node && (t_stack *)(stack->content)->ast_node->type == COMMAND)
            {
                free_char_array(((t_stack *)(stack->content))->ast_node->args, ((t_stack *)(stack->content))->ast_node->nb_args);
                ft_lstclear(&((t_stack *)(stack->content))->ast_node->redirections, NULL);
            }
            free((t_stack *)(stack->content)->ast_node);
        }
        if ((t_stack *)(stack->content)->symbol)
            free_char_array(((t_stack *)(stack->content))->values, ((t_stack *)(stack->content))->nb_values);
        free((t_stack *)(stack->content));
    }
}
