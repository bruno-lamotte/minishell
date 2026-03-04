/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 03:20:49 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/04 10:15:06 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_transition	*create_transition(char *symbol_name, t_state *dest_state)
{
	t_transition *transition;

	transition = malloc(sizeof(t_transition));
	if (!transition)
		return (NULL);
	transition->symbol = ft_strdup(symbol_name);
	if (!transition->symbol)
	{
		free(transition);
		return (/*JSP*/);
	}
	transition->dest_state = dest_state;
	return (transition);
}

t_state	*create_new_state(t_parser *data, t_state *state)
{
	t_state *new_state;

	new_state = malloc(sizeof(t_state));
	if (!new_state)
		return (NULL);
	new_state->id = ft_lstlast(data->states)->content->id + 1;
	new_state->items = NULL;
	return (new_state);
}

void	add_item_to_list(t_parser *data, t_state **new_state, t_item *item)
{
	t_item *new_item;

	new_item = create_new_item(item->rule_of_item, item->dot_pos + 1);
	if (!new_item)
		return (/*a completer*/);
	ft_lstadd_back(&(*new_state)->items, ft_lstnew(new_item));
}

void	add_transition_to_state(t_parser *data, t_state *new_state, t_symbol *symbol)
{
	t_state     *transition_state;

	transition_state = find_state(data, new_state);
	if (!transition_state)
	{
		ft_lstadd_back(&data->states, ft_lstnew(new_state));
		transition = create_transition(symbol->name, new_state);
	}
	else
    {
		transition = create_transition(symbol->name, transition_state);
        free(new_state);
    }
	ft_lstadd_back(&current_state->transitions, ft_lstnew(transition));
}

void	get_new_state(t_parser *data, t_state *current_state, t_state *new_state, t_item *item)
{
    t_symbol    *symbol;
	t_symbol    *next_symbol;

    symbol = get_symbol_after_dot(current_state->items->content);
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
	add_transition_to_state(data, new_state, symbol);

}

void	go_to(t_parser *data, t_state *state)
{
	t_state *new_state;
	t_symbol *symbol;
	t_list *seen_symbols;
	t_transition *transition;

	seen_symbols = NULL;
	while (state->items)
	{
		new_state = create_new_state(data, state);
		if (!new_state)
			return (/*a completer*/);
		symbol = get_symbol_after_dot(state->items->content);
		ft_lstadd_back(&seen_symbols, ft_lstnew(symbol->name));
		if (symbol && !does_list_contains_this_token(seen_symbols, symbol->name))
			get_new_state(data, current_state,new_state, state->items);
		state->items = state->items->next;
	}
	ft_lstclear(&seen_symbols, NULL);
}
