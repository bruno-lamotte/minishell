/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:49:37 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 21:02:43 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_of_args(t_parser *data, int lookahead)
{
	int		size;
	t_list	*stack;

	size = 0;
	stack = data->stack;
	while (lookahead--)
	{
		if (is_redirection_symbol((t_stack *)(stack->content))
			|| !ft_strcmp(((t_stack *)(stack->content))->symbol,
			"ASSIGNMENT_WORD"))
		{
			stack = stack->next;
			continue ;
		}
		if (((t_stack *)(stack->content))->ast_node)
			size += ((t_stack *)(stack->content))->ast_node->nb_args;
		else
			size += ((t_stack *)(stack->content))->nb_values;
		stack = stack->next;
	}
	return (size);
}

int	get_size_of_assignements(t_parser *data, int lookahead)
{
	int		size;
	t_list	*stack;

	size = 0;
	stack = data->stack;
	while (lookahead--)
	{
		if (((t_stack *)(stack->content))->ast_node)
			size += ((t_stack *)(stack->content))->ast_node->nb_assignments;
		else if (!ft_strcmp(((t_stack *)(stack->content))->symbol,
			"ASSIGNMENT_WORD"))
			size++;
		stack = stack->next;
	}
	return (size);
}

void	reduce_ast_command(t_parser *data, t_reduce_rule *rule,
		t_node_type node_type)
{
	t_ast	*ast_node;
	t_stack	*stack_node;
	int		lookahead;

	lookahead = rule->nb_items;
	stack_node = malloc(sizeof(t_stack));
	if (!stack_node)
		return ;
	ast_node = malloc(sizeof(t_ast));
	if (!ast_node)
		return ;
	ft_bzero(ast_node, sizeof(t_ast));
	ast_node->type = node_type;
	ast_node->nb_args = get_size_of_args(data, lookahead);
	ast_node->args = pop_args_from_stack(data, ast_node->nb_args);
	ast_node->redirections = pop_redirections_from_stack(data, lookahead);
	ast_node->nb_assignments = get_size_of_assignements(data, lookahead);
	ast_node->assignments = pop_assignements_from_stack(data,
			ast_node->nb_assignments);
	clear_stack_after_reduce(data, lookahead, 1);
	ft_bzero(stack_node, sizeof(t_stack));
	stack_node->ast_node = ast_node;
	stack_node->symbol = ft_strdup(rule->left_symbol);
	ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
}
