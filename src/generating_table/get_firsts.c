/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_firsts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:04:23 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/28 19:22:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	does_firsts_contains_this_token(t_list *firsts, char *token_name)
{
	while (firsts)
	{
		if (!ft_strcmp(firsts->content, token_name))
			return (1);
		firsts = firsts->next;
	}
	return (0);
}

int add_firsts_if_not_token(t_parser *data, t_rule *next_rule, t_symbol *left_symbol)
{
    t_list *new_list;
    t_list *new_node;
    
	new_list = get_symbol_from_rule(data, next_rule->left_symbol)->firsts;
	if (!new_list)
		return (0);
    while (new_list)
    {
        new_node = ft_lstnew(new_list->content);
        if (!new_list)
            return (0);
        if (does_firsts_contains_this_token(left_symbol->firsts, new_list->content))
	        ft_lstadd_back(&left_symbol->firsts, new_node);
        new_list = new_list->next;
    }
    return (1);
}

int add_first_if_token(t_symbol *left_symbol, t_symbol *right_symbol)
{
    t_list  new_list;
    
	new_list = ft_lstnew(right_symbol);
	if (!new_list)
		return (0);
	ft_lstadd_back(&left_symbol->firsts, new_list);
    return (1);
}
int should_look_for_next_right_symbol(t_symbol *left_symbol, t_rule rule)
{
	if (!rule->right_symbols->next)
		return (0);
    return (does_firsts_contains_this_token(left_symbol->firsts, "EMPTY") 
		&& rule->right_symbols->next->content);
}

void	get_first_dfs(t_parser *data, t_rule *rule, t_symbol *left_symbol, t_symbol *right_symbol)
{
	t_rule		*next_rule;

	while (1)
	{
		if (!does_firsts_contains_this_token(left_symbol->firsts, right_symbol->name))
		{
			if (symbol_is_token(right_symbol))
                if (!add_first_if_token(left_symbol, right_symbol))
                    return (/*JSP*/);
			else
			{
				next_rule = get_rule_from_symbol(data, right_symbol);
				if (rule != next_rule) 
                /*ce if n est peut etre pas suffisant :
                je ne sais pas si une grammaire peut boucler a une ou plus regles d intervales.
                si c est le cas je compte mettre en place un bitsmask qu un handler actualise
                a chaque ouverture et fermeture de stack
                pour etre sur de ne pas ouvrir deux fenetres pour la meme regle*/
					get_first_dfs(data, next_rulem, left_symbol, get_symbol_from_rule(data, next_rule->right_symbols->content));
                if (!add_firsts_if_not_token(data, next_rule, left_symbol))
                    return (/*JSP*/);
			}
		}
        if (should_look_for_next_right_symbol(left_symbol, rule))
            right_symbol = get_symbol_from_rule(data, rule->right_symbols->next->content);
        // else if (left_symbol == data->rules->next->content->left_symbol)
        //     data->rules = data->rules->next;
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
		left_symbol = get_symbol_from_rule(data, current_rule->content->left_symbol);
		right_symbol = get_symbol_from_rule(data, current_rule->content->right_symbols->content);
		get_first_dfs(data, current_rule->content, left_symbol, right_symbol);
		current_rule = current_rule->next;
	}
}
