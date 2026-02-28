/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:36 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/28 19:31:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rule	*get_rule_from_symbol(t_parser *data, char *symbol)
{
	while (data->rules)
	{
		if (!ft_strcmp(data->rules->content->left_symbol, symbol))
			return (data->rules->content);
		else
			data->rules = data->rules->next;
	}
	return (NULL);
}

t_symbol	*get_symbol_from_rule(t_parser *data, char *left_symbol)
{
	while (data->symbols)
	{
		if (!ft_strcmp(data->symbols->content->name, left_symbol))
			return (data->symbols->content);
		else
			data->symbols = data->symbols->next;
	}
	return (NULL);
}
int	symbol_is_token(char *name)
{
	return (&name < 97);
}

void    complete_symbol_name(t_parser *data, t_symbol **symbol, char *name)
{
    (*symbol)->name = ft_strdup(name);
    if (!(*symbol)->name)
        return (/*a completer*/);
}

// int symbol_already_parsed(t_list *symbols, char *left_symbol)
// {
//     while (data->symbols)
// 		{
// 			if (ft_strcmp(data->symbols->content->name,
// 					data->rules->content->left_symbol))
//                 return (1);
// 			else
// 				data->symbols = data->symbols->next;
// 		}
//     return (0);
// }

void	create_symbols_from_rules(t_parser *data)
{
	t_symbol	*new_symbol;
    t_list      *new_list;

	while (data->rules)
	{

		new_symbol = malloc(sizeof(t_symbol));
		if (!new_symbol)
			return (/*error jsp*/);
        complete_symbol_name(data, &new_symbol, data->rules->content->left_symbol);
        new_list = ft_lstnew(new_symbol);
        if (!new_list)
            return (/*je ne sais tjrs pas*/);
        ft_lstadd_back(&data->symbol, new_list);
	}
	get_first(data);
}
