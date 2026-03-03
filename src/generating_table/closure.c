/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 20:55:38 by marvin            #+#    #+#             */
/*   Updated: 2026/03/01 20:55:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_symbol *get_symbol_from_list(t_list *right_symbols, int dot_pos)
{
    t_list  *current;

    current = right_symbols;
    while (dot_pos)
    {
        current = current->next;
    }
    return (get_symbol_from_rule(current->content));
}

t_symbol *get_symbol_after_dot(t_item *item)
{
    char *symbol_name;

    if (item->dot_pos >= item->rule_of_item->nb_items)
        return (NULL);
    symbol = get_symbol_from_list(item->rule_of_item->right_symbols, item->dot_pos);
    if (!symbol_is_token(symbol->name))
        return (symbol);
    return (NULL);
}

void  closure(t_data *data, t_state *state)
{
    t_list  *current_item;
    t_symbol *symbol_after_dot;
    t_list   *rule_of_item;
    t_item   *new_item;

    current_item = state->items;
    while (current_item)
    {
        symbol_after_dot = get_symbol_after_dot(current_item->content);
        if (symbol_after_dot)
        {
            rule_of_item = get_rule_from_symbol(data, symbol_after_dot->name);
            while (rule_of_item)
            {
                new_item = create_new_item(rule_of_item, 0);
                if (!does_list_contains_this_symbol(state->items, new_item))
                    ft_lstadd_back(&state->items, ft_lstnew(new_item));
                if (ft_strcmp(rule_of_item->content->left_symbol, symbol_after_dot->name))
                    rule_of_item = rule_of_item->next;
                else
                    break ;
            }
        }
        current_item = current_item->next;
    }
}
