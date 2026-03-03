/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_follows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:34:18 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/27 16:44:54 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void add_eof_to_start_follow(t_parser *data)
{
    t_symbol    *symbol;
    t_list      *new_list;
    
    symbol = get_symbol_from_rule(data, data->rules->content->left_symbol);
    new_list = ft_lstnew("$");
    if (!new_list)
        return (/*JSP*/);
    ft_lstadd_back(&symbol->follows, new_list);
}

void get_follows(t_parser *data)
{
    t_list  *current_rule;

    current_rule = data->rules;
    add_eof_to_follow(data);
    lstget_symbol_from_rule(data, current_rule->content->left_symbol);
    while (current_rule)
    {
        
    }
}