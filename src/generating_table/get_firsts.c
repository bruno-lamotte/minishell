/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_firsts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:04:23 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/27 12:16:32 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	does_firsts_contains_this_token(t_list firsts, char *token_name)
{
	while (firsts)
	{
		if (!ft_strcmp(firsts->content, token_name))
			return (1);
		firsts = firsts->next;
	}
	return (0);
}

void	get_first_loop(t_parser *data, t_rule *rule, t_symbol *left_symbol, t_symbol *right_symbol)
{
	t_list		*new_list;
	t_rule		*next_rule;

	next_rule = NULL;
	while (1)
	{
		if (!does_firsts_contains_this_token(left_symbol->firsts, right_symbol))
		{
			if (symbol_is_token(right_symbol))
			{
				new_list = ft_lstnew(right_symbol);
				if (!new_list)
					return (/*JSP*/);
				ft_lstadd_back(&left_symbol->firsts, new_list);
			}
			else
			{
				next_rule = get_rule_from_symbol(data, right_symbol);
				if (!rule == next_rule)
					get_first_loop(data, next_rule);
				new_list = get_symbol_from_rule(data, next->rule->left_symbol)->firsts;
				if (!new_list)
					return (/*JSP*/);
				ft_lstadd_back(&left_symbol->firsts, new_list);
			}
		}
			if (does_firsts_contains_this_token(left_symbol->firsts, "EMPTY") && rule->right_symbols->next)
				right_symbol = get_symbol_from_rule(data, rule->right_symbols->next->content)
			else if (left_symbol == data->rules->next->content->left_symbol)
				data->rules = data->rules->next;
			else
				return ;
	}
}

void	get_firsts(t_parser *data)
{
	t_symbol	*left_symbol;
	t_symbol	*right_symbol;

	while (data->rules)
	{
		left_symbol = get_symbol_from_rule(data, rule->left_symbol);
		right_symbol = get_symbol_from_rule(data, rule->right_symbols->content);

			get_first_loop(data, data->rules->content, left_symbol, right_symbol);
		data->rules = data->rules->next;
	}
}
