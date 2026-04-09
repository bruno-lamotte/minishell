/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:02:14 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 19:26:22 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_bang_prefix(t_parser *data, t_reduce_rule *rule, t_ast *ast)
{
	if (rule->nb_items != 2 || !ast)
		return (0);
	if (!((t_stack *)(data->stack->next->content))->symbol)
		return (0);
	return (!ft_strcmp(((t_stack *)(data->stack->next->content))->symbol,
		"BANG"));
}

static int	reduce_existing_ast(t_parser *data, t_reduce_rule *rule,
		t_stack *stack_node, t_ast *ast)
{
	if (rule->nb_items == 1 && ast)
	{
		stack_node->ast_node = ast;
		((t_stack *)(data->stack->content))->ast_node = NULL;
		clear_stack_after_reduce(data, 1, 0);
		return (1);
	}
	if (has_bang_prefix(data, rule, ast))
	{
		stack_node->ast_node = ast;
		stack_node->ast_node->is_bang = !stack_node->ast_node->is_bang;
		((t_stack *)(data->stack->content))->ast_node = NULL;
		clear_stack_after_reduce(data, 2, 0);
		return (1);
	}
	return (0);
}

void	reduce_symbol(t_parser *data, t_reduce_rule *rule)
{
	t_stack	*stack_node;
	t_ast	*ast;

	stack_node = malloc(sizeof(t_stack));
	if (!stack_node)
		return ;
	ft_bzero(stack_node, sizeof(t_stack));
	stack_node->symbol = ft_strdup(rule->left_symbol);
	ast = ((t_stack *)(data->stack->content))->ast_node;
	if (!reduce_existing_ast(data, rule, stack_node, ast))
	{
		stack_node->nb_values = get_size_of_args(data, rule->nb_items);
		stack_node->values = pop_args_from_stack(data, stack_node->nb_values);
		clear_stack_after_reduce(data, rule->nb_items, 0);
	}
	ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
}
