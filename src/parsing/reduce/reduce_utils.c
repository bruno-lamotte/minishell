/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:45:50 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 22:29:25 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type	get_node_type_from_rule(t_reduce_rule *rule, t_list *stack)
{
	if (ft_strnstr(rule->left_symbol, "cmd", ft_strlen(rule->left_symbol))
		|| ft_strnstr(rule->left_symbol, "simple_command",
			ft_strlen(rule->left_symbol)))
		return (COMMAND);
	if (ft_strnstr(rule->left_symbol, "subshell",
			ft_strlen(rule->left_symbol)))
		return (SUBSHELL);
	if (ft_strnstr(rule->left_symbol, "pipeline", ft_strlen(rule->left_symbol))
		&& rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "PIPE"))
		return (PIPE);
	if (rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "SEMI"))
		return (SEQUENCE);
	if (ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
		&& rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "AND_IF"))
		return (AND);
	if (ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
		&& rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "OR_IF"))
		return (OR);
	return (UNKNOWN);
}

int	is_node_already_type(t_parser *data, int lookahead, t_node_type node_type)
{
	t_list	*stack;

	stack = data->stack;
	while (lookahead--)
		stack = stack->next;
	if (((t_stack *)(stack->content))->ast_node
		&& ((t_stack *)(stack->content))->ast_node->type == node_type)
		return (1);
	return (0);
}

int	get_symbol_nbr(t_parser *data, char *symbol)
{
	int	i;

	i = 0;
	while (data->symbols[i] && ft_strcmp(data->symbols[i], symbol))
		i++;
	if (!data->symbols[i])
		return (-1);
	return (i);
}

int	get_next_state_after_reduce(t_parser *data, int **table,
		t_reduce_rule *rule)
{
	int	state_id;
	int	symbol_nbr;

	symbol_nbr = get_symbol_nbr(data, rule->left_symbol);
	state_id = ((t_stack *)(data->stack->next->content))->state_id;
	return (table[state_id][symbol_nbr]);
}
