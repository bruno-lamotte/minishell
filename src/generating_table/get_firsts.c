/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_firsts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:04:23 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/09 20:29:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	does_list_contains_this_symbol(t_list *list, char *name)
{
	while (list)
	{
		if (!ft_strcmp((char *)list->content, name))
			return (1);
		list = list->next;
	}
	return (0);
}

int add_firsts_if_not_token(t_parser *data, t_rule *next_rule, t_symbol *left_symbol)
{
    t_list *new_list;
    t_list *new_node;
    
	new_list = get_symbol_from_name(data, next_rule->left_symbol)->firsts;
	if (!new_list)
		return (0);
    while (new_list)
    {
        new_node = ft_lstnew(new_list->content);
        if (!new_node)
            return (0);
        if (!does_list_contains_this_symbol(left_symbol->firsts, (char *)new_list->content))
	        ft_lstadd_back(&left_symbol->firsts, new_node);
        new_list = new_list->next;
    }
    return (1);
}

int add_first_if_token(t_symbol *left_symbol, t_symbol *right_symbol)
{
    t_list  *new_list;
    
	new_list = ft_lstnew(right_symbol->name);
	if (!new_list)
		return (0);
	ft_lstadd_back(&left_symbol->firsts, new_list);
    return (1);
}
int should_look_for_next_right_symbol(t_symbol *left_symbol, t_rule *rule)
{
	if (!rule->right_symbols->next)
		return (0);
    return (does_list_contains_this_symbol(left_symbol->firsts, "EMPTY") 
		&& rule->right_symbols->next->content);
}

void	get_first_dfs(t_parser *data, t_rule *rule, t_symbol *left_symbol, t_symbol *right_symbol)
{
	t_list	*rule_node;
	t_rule	*next_rule;

	while (1)
	{
		if (!does_list_contains_this_symbol(left_symbol->firsts, right_symbol->name))
		{
			if (symbol_is_token(right_symbol->name))
			{
                if (!add_first_if_token(left_symbol, right_symbol))
                    return /*JSP*/;
			}
			else
			{
				rule_node = get_rule_from_symbolname(data, right_symbol->name);            
				next_rule = (t_rule *)rule_node->content;
				if (rule != next_rule) //attention aux règles récursives indirectes
					get_first_dfs(data, next_rule, left_symbol, get_symbol_from_name(data, (char *)next_rule->right_symbols->content));
                if (!add_firsts_if_not_token(data, next_rule, left_symbol))
                    return /*JSP*/;
			}
		}
        if (should_look_for_next_right_symbol(left_symbol, rule))
            right_symbol = get_symbol_from_name(data, (char *)rule->right_symbols->next->content);
        else
            return ;
	}
}

void	get_firsts(t_parser *data)
{
	t_symbol	*left_symbol;
	t_symbol	*right_symbol;
    t_list      *current_rule;

    current_rule = data->rules;
	while (current_rule)
	{
		left_symbol = get_symbol_from_name(data, ((t_rule *)current_rule->content)->left_symbol);
		right_symbol = get_symbol_from_name(data, (char *)((t_rule *)current_rule->content)->right_symbols->content);
		get_first_dfs(data, (t_rule *)current_rule->content, left_symbol, right_symbol);
		current_rule = current_rule->next;
	}
}
