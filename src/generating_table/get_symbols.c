/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:36 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/09 18:57:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_rule_from_symbolname(t_parser *data, char *symbol)
{
	t_list	*current;
	
	current = data->rules;
	while (current)
	{
		if (!ft_strcmp(((t_rule *)current->content)->left_symbol, symbol))
			return (current);
		else
			current = current->next;
	}
	return (NULL);
}

t_symbol	*get_symbol_from_name(t_parser *data, char *left_symbol)
{
	t_list	*current;

	current = data->symbols;
	while (current)
	{
		if (!ft_strcmp(((t_symbol *)current->content)->name, left_symbol))
			return ((t_symbol *)current->content);
		else
			current = current->next;
	}
	return (NULL);
}
int	symbol_is_token(char *name)
{
	return (*name < 97);
}

void    complete_symbol_name(t_symbol **symbol, char *name)
{
    (*symbol)->name = ft_strdup(name);
    if (!(*symbol)->name)
        return /*a completer*/;
}

int symbol_already_parsed(t_list *symbols, char *left_symbol)
{
    while (symbols)
		{
			if (!ft_strcmp(((t_symbol *)symbols->content)->name, left_symbol))
                return (1);
			else
				symbols = symbols->next;
		}
    return (0);
}

void    add_symbol_if_not_exists(t_parser *data, char *name, int *nbr)
{
    t_symbol *new_symbol;

    if (!name || symbol_already_parsed(data->symbols, name))
        return ;
    new_symbol = malloc(sizeof(t_symbol));
    if (!new_symbol)
        return ;
    ft_bzero(new_symbol, sizeof(t_symbol));
    complete_symbol_name(&new_symbol, name);
    new_symbol->nbr = (*nbr)++;
    ft_lstadd_back(&data->symbols, ft_lstnew(new_symbol));
}

void    get_symbols(t_parser *data)
{
    t_list  *current_rule;
    t_list  *right_symbol;
    int     nbr;

	nbr = 0;
    add_symbol_if_not_exists(data, "$", &nbr);
    current_rule = data->rules;
    while (current_rule)
    {
        add_symbol_if_not_exists(data, ((t_rule *)current_rule->content)->left_symbol, &nbr);
        right_symbol = ((t_rule *)current_rule->content)->right_symbols;
    	while (right_symbol)
        {
            add_symbol_if_not_exists(data, (char *)right_symbol->content, &nbr);
            right_symbol = right_symbol->next;
        }            
       current_rule = current_rule->next;
    }
}
