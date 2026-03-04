/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:36 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/04 01:58:07 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_rule_from_symbolname(t_parser *data, char *symbol)
{
	t_list	*current;
	
	current = data->rules;
	while (current)
	{
		if (!ft_strcmp(current->content->left_symbol, symbol))
			return (current);
		else
			current = current->next;
	}
	return (NULL);
}

t_symbol	*get_symbol_from_rule(t_parser *data, char *left_symbol)
{
	t_list	*current;

	current = data->symbols;
	while (current)
	{
		if (!ft_strcmp(current->content->name, left_symbol))
			return (current->content);
		else
			current = current->next;
	}
	return (NULL);
}
int	symbol_is_token(char *name)
{
	return (*name < 97);
}

void    complete_symbol_name(t_parser *data, t_symbol **symbol, char *name)
{
    (*symbol)->name = ft_strdup(name);
    if (!(*symbol)->name)
        return (/*a completer*/);
}

int symbol_already_parsed(t_list *symbols, char *left_symbol)
{
    while (symbols)
		{
			if (ft_strcmp(symbols->content->name, left_symbol))
                return (1);
			else
				symbols = symbols->next;
		}
    return (0);
}

void	create_symbols_from_rules(t_parser *data)
{
	t_symbol	*new_symbol;
    t_list      *new_list;
	t_list	*current_rule;
	
	current_rule = data->rules;
	while (current_rule)
	{

		new_symbol = malloc(sizeof(t_symbol));
		if (!new_symbol)
			return (/*error jsp*/);
        complete_symbol_name(data, &new_symbol, current_rule->content->left_symbol);
        new_list = ft_lstnew(new_symbol);
        if (!new_list)
            return (/*je ne sais tjrs pas*/);
        ft_lstadd_back(&data->symbols, new_list);
		while (symbol_already_parsed(data->symbols, current_rule->content->left_symbol))
			current_rule = current_rule->next;
	}
	get_first(data);
}
