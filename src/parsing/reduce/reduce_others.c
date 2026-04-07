/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:57:55 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 18:31:49 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_background_rule(t_reduce_rule *rule, t_list *stack)
{
	if (!ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
		|| rule->nb_items != 3)
		return (0);
	if (((t_stack *)(stack->next->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->next->content))->symbol,
		"BACKGROUND"))
		return (1);
	if (((t_stack *)(stack->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->content))->symbol, "BACKGROUND"))
		return (1);
	return (0);
}

int	reduce_booleans(t_parser *data, t_reduce_rule *rule)
{
	t_list	*stack;

	stack = data->stack;
	if (ft_strnstr(rule->left_symbol, "pipeline", ft_strlen(rule->left_symbol))
		&& rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol
		&& !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "BANG"))
	{
		((t_stack *)(stack->content))->ast_node->is_bang = 1;
		return (1);
	}
	if (is_background_rule(rule, stack))
	{
		((t_stack *)(stack->content))->ast_node->is_async = 1;
		return (1);
	}
	return (0);
}
