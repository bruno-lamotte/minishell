/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_follows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:34:18 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/04 10:39:28 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_dollar_to_start_symbol(t_parser *data)
{
    t_list      *new_list;
    t_symbol    *symbol;

    symbol = get_symbol_from_rule(data, data->rules->content->left_symbol);
    new_list = ft_lstnew("$");
    if (!new_list)
        return (/*a completer*/);
    ft_lstadd_back(&symbol->follows, new_list);
}

int add_follows_from_list(t_symbol **symbol, t_symbol *next_symbol)
{
    t_list *new_list;
    t_list *new_node;
    int     has_added;
    
    has_added = 0;
    new_list = next_symbol->firsts;
    if (!new_list)
        return (0);
    while (new_list)
    {
        if (ft_strcmp(new_list->content, "EMPTY"))
            new_list = new_list->next;
        else if (!does_list_contains_this_symbol((*symbol)->follows, new_list->content))
        {
            new_node = ft_lstnew(new_list->content);
            if (!new_node)
                return (/*jsp*/);
            has_added++;
            ft_lstadd_back(&(*symbol)->follows, new_node);
            new_list = new_list->next;
        }
    }
    return (has_added);
}

int contains_empty_in_firsts(t_symbol *symbol)
{
    t_list *current;

    current = symbol->firsts;
    while (current)
    {
        if (!ft_strcmp(current->content, "EMPTY"))
            return (1);
        current = current->next;
    }
    return (0);
}

void    update_follows(t_parser *data, t_list *current_rule, int *added)
{
    t_symbol *tmp_symbol;
    t_symbol *tmp_next_symbol;
    
    while (current_rule)
    {
        tmp_symbol = get_symbol_from_rule(data, current_rule->right_symbols->content);
        while (tmp_symbol->next)
        {
            tmp_next_symbol = get_symbol_from_rule(data, tmp_symbol->next->content);
            *added += add_follows_from_list(&tmp_symbol, tmp_next_symbol);
            if (contains_empty_in_firsts(tmp_next_symbol))
                *added += add_follows_from_list(&tmp_symbol, get_symbol_from_rule(data, current_rule->left_symbol));
            tmp_symbol = tmp_next_symbol;
        }
        if (!tmp_symbol->next && ft_strcmp(tmp_symbol->name, current_rule->left_symbol))
            *added += add_follows_from_list(&tmp_symbol, get_symbol_from_rule(data, current_rule->left_symbol));
        current_rule = current_rule->next;
    }
}

void    get_follows(t_parser *data)
{
    t_list  *current_rule;
    int     added;

    added = 1;
    current_rule = data->rules;
    add_dollar_to_start_symbol(data);
    while (has_added)
    {
        added = 0;
        update_follows(data, current_rule, &added);
    }
}
