/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 02:26:54 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/20 20:31:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_transition_from_symbol(t_state *state, char *symbol_name)
{
    t_list *transition;

    transition = state->transitions;
    while (transition)
    {
        if (!ft_strcmp(((t_transition *)transition->content)->symbol, symbol_name))
            return (((t_transition *)transition->content)->dest_state->id);
        transition = transition->next;
    }
    return (0);
}

void fill_table_when_reduce(t_parser *data, int ***table, t_list *state, t_list *item)
{
    t_rule      *rule;
    t_symbol    *symbol;
    t_list      *follow;

    rule = ((t_item *)item->content)->rule_of_item;
    follow = get_symbol_from_name(data, ((t_item *)item->content)->rule_of_item->left_symbol)->follows;
    while (follow)
    {
        symbol = get_symbol_from_name(data, (char *)follow->content);
        if (rule->id == 1 && !ft_strcmp(symbol->name, "$"))
            (*table)[((t_state *)state->content)->id][symbol->nbr] = ACCEPTED;
        else
            (*table)[((t_state *)state->content)->id][symbol->nbr] = -(rule->id);
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
        item = ((t_state *)state->content)->items;
        while (item)
        {
            symbol = get_symbol_after_dot(data, (t_item *)item->content);
            if (symbol)
                (*table)[((t_state *)state->content)->id][symbol->nbr] = get_transition_from_symbol((t_state *)state->content, symbol->name);
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
    t_item  *first_item;

    first_state = malloc(sizeof(t_state));
    if (!first_state)
        return (/*JSP*/NULL);
    ft_bzero(first_state, sizeof(t_state));
    first_state->id = 0;
    first_item = create_new_item((t_rule *)data->rules->content, 0);
    ft_lstadd_back(&first_state->items, ft_lstnew(first_item));
    first_state->transitions = NULL;
    return (first_state);
}
void    get_states(t_parser *data)
{
    t_state *first_state;
    t_list  *current;

    first_state = initialize_first_state(data);
    ft_lstadd_back(&data->states, ft_lstnew(first_state)); 
    closure(data, first_state);
    current = data->states;
    while (current)
    {
        go_to(data, (t_state *)current->content);
        current = current->next;
    }
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
    int     **table;
    int     size;
    int     nb_symbols;
    int     i;
    
    i = 0;
    parse_grammar(data);
    get_symbols(data);
    get_firsts(data);
    get_follows(data);
    get_states(data);
    size = ft_lstsize(data->states);
    nb_symbols = ft_lstsize(data->symbols);
    table = malloc(sizeof(int *) * (size + 1));
    if (!table)
        return (NULL);
    while (i < size)
    {
        table[i] = malloc(sizeof(int) * nb_symbols);
        ft_bzero(table[i], sizeof(int) * nb_symbols);
        i++;
    }
    table[size] = NULL;
    fill_parsing_table(data, &table);
    return (table);
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
    print_table_in_c(table, ft_lstsize(data->states), ft_lstsize(data->symbols));
    print_rules_in_c(data->rules);
    //print_table(table, data);
    return (0);
}
