/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:45:50 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 06:56:41 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type get_node_type_from_rule(t_reduce_rule *rule, t_list *stack)
{
    if (ft_strnstr(rule->left_symbol, "cmd", ft_strlen(rule->left_symbol)))
        return (COMMAND);
    if (ft_strnstr(rule->left_symbol, "subshell", ft_strlen(rule->left_symbol)))
        return (SUBSHELL);
    if (ft_strnstr(rule->left_symbol, "pipeline", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && (t_stack *)(stack->next->content)->symbol 
        && !ft_strcmp((t_stack *)(stack->next->content)->symbol, "PIPE"))
        return (PIPE);
    if (ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && (t_stack *)(stack->next->content)->symbol 
        && !ft_strcmp((t_stack *)(stack->next->content)->symbol, "SEMI"))
        return (SEQUENCE);
    if (ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && (t_stack *)(stack->next->content)->symbol 
        && !ft_strcmp((t_stack *)(stack->next->content)->symbol, "AND_IF"))
        return (AND);
    if (ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && (t_stack *)(stack->next->content)->symbol 
        && !ft_strcmp((t_stack *)(stack->next->content)->symbol, "OR_IF"))
        return (OR);
    return (UNKNOWN);
}

t_rule  *get_rule_from_id(t_slr1 *data, int id)
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

int is_node_already_type(t_slr1 *data, int lookahead, t_node_type node_type)
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

void    clear_stack_after_reduce(t_slr1 *data, int nb_items, int should_free_ast)
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
        if ((t_stack *)(stack->content)->values)
            free_char_array(((t_stack *)(stack->content))->values, ((t_stack *)(stack->content))->nb_values);
        if ((t_stack *)(stack->content)->symbol)
            free(((t_stack *)(stack->content))->symbol);
        free((t_stack *)(stack->content));
    }
}
