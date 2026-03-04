/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2026/03/01 20:55:47 by marvin            #+#    #+#             */
/*   Updated: 2026/03/04 01:22:38 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state *create_new_state(t_data *data, t_state *state)
{
    t_state *new_state;

    new_state = malloc(sizeof(t_state));
    if (!new_state)
        return (NULL);
    new_state->id = ft_lstlast(data->states)->content->id + 1;
    new_state->items = NULL;
    return (new_state);
}
void	add_item_to_list(t_data *data, t_state **new_state, t_item *item)
{
	t_item *new_item;

	new_item = create_new_item(item->rule_of_item, item->dot_pos + 1);
	if (!new_item)
		return (/*a completer*/);
	ft_lstadd_back(&(*new_state)->items, ft_lstnew(new_item));
}

void	go_to(t_data *data, t_state *new_state, t_item *item, t_symbol *symbol)
{
	t_symbol *next_symbol;

	while (symbol)
	{
		add_item_to_list(data, &new_state, item->content);
		item = item->next;
		next_symbol = get_symbol_after_dot(item->content);
		while (next_symbol && !ft_strcmp(next_symbol->name, symbol->name))
			next_symbol = next_symbol->next;
		if (!next_symbol)
			break ;
		else
			symbol = next_symbol;
	}
	closure(data, new_state);
	if (!state_already_exists(data, new_state))
		ft_lstadd_back(&data->states, ft_lstnew(new_state));
	else
		free(new_state);
}

void	go_to_main(t_data *data, t_state *state)
{
	t_state *new_state;
    t_symbol *symbol;
    t_list    *seen_symbols;

    seen_symbols = NULL;
    while (state->items)
    {
        new_state = create_new_state(data,state);
	    if (!new_state)
		    return (/*a completer*/);
        symbol = get_symbol_after_dot(state->items->content);
        ft_lstadd_back(&seen_symbols, ft_lstnew(symbol->name));
        if (symbol && !does_list_contains_this_token(seen_symbols, symbol->name))
            go_to(data, new_state, state->items, symbol);
        state->items = state->items->next;
    }
}
