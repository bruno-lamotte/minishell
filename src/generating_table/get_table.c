/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 02:26:54 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/06 19:06:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_transition_from_symbol(t_state *state, char *symbol_name)
{
    t_list *transition;

    transition = state->transition;
    while (transition)
    {
        if (!ft_strcmp(transition->content->symbol))
            return (transition->content->dest_state->id);
        transition = transition->next;
    }
    return (NULL);
}

void fill_table_when_reduce(t_parser *data, int ***table, t_list *state, t_list *item)
{
    t_rule      *rule;
    t_symbol    *symbol;
    t_list      *follow;

    rule = get_rule_from_symbolname(item->content->rule_of_item->left_symbol);
    follow = rule->follows;
    while (follow)
    {
        symbol = get_symbol_from_name(follow->content);
        if (ft_strcmp(symbol->name, "$"))
            table[state->content->id][symbol->nbr] = ACCEPTED;
        else
            table[state->content->id][symbol->nbr] = -rule->id;
        follow = follow->next;
    }
}

void    fill_parsing_table(t_parser *data, int ***table)
{
    t_symbol    *symbol;
    t_list      *state;
    t_list      *item;

    state = data->states;
    while (state)
    {
        item = current_data->content->items;
        while (item)
        {
            symbol = get_symbol_after_dot(item->content);
            if (table[state->content->id][symbol->nbr])
                return (/*jsp*/ printf("%s", "ERROR : possible conflict conflict"));
            if (symbol)
                table[state->content->id][symbol->nbr] = get_transition_from_symbol(state->content, symbol->name);
            else
                fill_table_when_reduce(data, table, state, item);
            item = item->next;
        }
        state = state->next;
    }
}

t_state *initialize_first_state(t_parser *data)
{
    t_state *first_state;
    t_state *first_item;

    first_state = malloc(sizeof(t_state));
    if (!first_state)
        return (/*JSP*/);
    first_state->id = 0;
    first_item = create_new_item(data->rules->content, 0);
    ft_lstadd_back(&first_state->items, ft_lstnew(first_item));
    first_state->transitions = NULL;
    return (first_state);
}
void    get_states(t_parser *data)
{
    t_state *first_state;

    first_state = initialize_first_state(data);
    closure(first_state);
    go_to(first_state);
}

void    initialize_data(t_parser *data)
{
    data->tokens = NULL;
    data->rules = NULL;
    data->symbols = NULL;
    data->states = NULL;
}

int    **create_parsing_table(t_parser *data)
{
    int **table;
    
    get_rules(data);
    get_symbols(data);
    get_firsts(data);
    get_follows(data);
    get_states(data);
    table = malloc(sizeof(int *) * (ft_lstsize(data->states) + 1));
    if (!table)
        return (NULL);
    ft_bzero(table);
    return (fill_parsing_table(data, &table));
}

int main(void)
{
    int         **table;
    t_parser    *data;

    data = malloc(sizeof(t_parser));
    if (!data)
        return (1);
    initialize_data(data);
    table = create_parsing_table(data);
    print_table(table);
    return (0);
}
