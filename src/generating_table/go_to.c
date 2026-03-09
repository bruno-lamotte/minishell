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
		return (/*JSP*/NULL);
	}
	transition->dest_state = dest_state;
	return (transition);
}

t_state	*create_new_state(t_parser *data)
{
	t_state *new_state;

	new_state = malloc(sizeof(t_state));
	if (!new_state)
		return (NULL);
	if (!data->states)
	new_state->id = 0;
	else
		new_state->id = ((t_state *)ft_lstlast(data->states)->content)->id + 1;
	new_state->items = NULL;
	return (new_state);
}

void	add_item_to_list(t_state **new_state, t_item *item)
{
	t_item *new_item;

	new_item = create_new_item(item->rule_of_item, item->dot_pos + 1);
	if (!new_item)
		return /*a completer*/;
	ft_lstadd_back(&(*new_state)->items, ft_lstnew(new_item));
}

int are_items_equal(t_item *i1, t_item *i2)
{
    return (i1->rule_of_item == i2->rule_of_item && i1->dot_pos == i2->dot_pos);
}

t_state	*find_state(t_parser *data, t_state *new_state)
{
	t_list	*current_state;
	t_list	*tmp_item1;
	t_list	*tmp_item2;

	current_state = data->states;
	while (current_state)
	{
		tmp_item1 = ((t_state *)current_state->content)->items;
		tmp_item2 = new_state->items;
		if (ft_lstsize(((t_state *)current_state->content)->items) != ft_lstsize(new_state->items))
		{
			current_state = current_state->next;
			continue ;
		}
		while (tmp_item1 && tmp_item2)
		{
			if (!are_items_equal((t_item *)tmp_item1->content, (t_item *)tmp_item2->content))
					return ((t_state *)current_state->content);
			tmp_item1 = tmp_item1->next;
			tmp_item2 = tmp_item2->next;
		}
		current_state = current_state->next;
	}
	return (NULL);
}

void	add_transition_to_state(t_parser *data, t_state *current_state, t_state *new_state, t_symbol *symbol)
{
	t_state     	*transition_state;
	t_transition	*transition;

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

void    get_new_state(t_parser *data, t_state *current_state, t_state *new_state, t_symbol *target_symbol)
{
    t_list *current_item;
    t_symbol *symbol;

    current_item = current_state->items;
    while (current_item)
    {
        symbol = get_symbol_after_dot(data, (t_item *)current_item->content);
        if (symbol && !ft_strcmp(symbol->name, target_symbol->name))
        {
            add_item_to_list(&new_state, (t_item *)current_item->content);
        }
        current_item = current_item->next;
    }
    closure(data, new_state);
    add_transition_to_state(data, current_state, new_state, target_symbol);
}

void	go_to(t_parser *data, t_state *state)
{
	t_list *current_item;
	t_state *new_state;
	t_symbol *symbol;
	t_list *seen_symbols;

	seen_symbols = NULL;
	current_item = state->items;
	while (current_item)
	{
		new_state = create_new_state(data);
		if (!new_state)
			return /*a completer*/;
		symbol = get_symbol_after_dot(data, (t_item *)current_item->content);
		if (!symbol)
		{
			free(new_state);
			current_item = current_item->next;
			continue ;
		}
		if (!does_list_contains_this_symbol(seen_symbols, symbol->name))
		{
			ft_lstadd_back(&seen_symbols, ft_lstnew(symbol->name));
			get_new_state(data, state, new_state, symbol);
		}
		current_item = current_item->next;
	}
	ft_lstclear(&seen_symbols, NULL);
}
