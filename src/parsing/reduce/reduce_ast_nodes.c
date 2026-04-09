/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_ast_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:11:47 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 15:53:01 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_subshell_redirections(t_parser *data, t_reduce_rule *rule)
{
	t_list	*tmp_list;

	tmp_list = ((t_stack *)(data->stack->content))->ast_node->redirections;
	((t_stack *)(data->stack->content))->ast_node->redirections
		= pop_redirections_from_stack(data, rule->nb_items);
	ft_lstclear(&tmp_list, NULL);
	((t_stack *)(data->stack->content))->symbol = ft_strdup(rule->left_symbol);
}

void	reduce_ast_subshell(t_parser *data, t_reduce_rule *rule,
		t_node_type node_type)
{
	t_ast	*ast_node;
	t_stack	*stack_node;

	if (rule->nb_items == 2)
		return (set_subshell_redirections(data, rule));
	stack_node = malloc(sizeof(t_stack));
	ast_node = malloc(sizeof(t_ast));
	if (!ast_node || !stack_node)
		return ;
	ft_bzero(stack_node, sizeof(t_stack));
	ft_bzero(ast_node, sizeof(t_ast));
	ast_node->type = node_type;
	ast_node->nb_children = 1;
	ast_node->children = malloc(sizeof(t_ast *) * (ast_node->nb_children + 1));
	if (!ast_node->children)
		return ;
	ast_node->children[0] = ((t_stack *)(data->stack->next->content))->ast_node;
	stack_node->symbol = ft_strdup(rule->left_symbol);
	stack_node->ast_node = ast_node;
	clear_stack_after_reduce(data, rule->nb_items, 0);
	ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
}

void	reduce_multiple_pipes(t_parser *data, t_reduce_rule *rule)
{
	t_list	*stack_node_to_update;
	t_stack	*stack_node;

	stack_node_to_update = data->stack;
	while (rule->nb_items--)
		stack_node_to_update = stack_node_to_update->next;
	stack_node = stack_node_to_update->content;
	stack_node->symbol = ft_strdup(rule->left_symbol);
	clear_stack_after_reduce(data, 2, 0);
}

void	reduce_ast_control(t_parser *data, t_reduce_rule *rule,
		t_node_type node_type)
{
	t_ast	*ast_node;
	t_stack	*stack_node;

	ast_node = malloc(sizeof(t_ast));
	stack_node = malloc(sizeof(t_stack));
	if (!ast_node || !stack_node)
		return ;
	ft_bzero(ast_node, sizeof(t_ast));
	ft_bzero(stack_node, sizeof(t_stack));
	ast_node->type = node_type;
	ast_node->nb_children = 2;
	ast_node->children = malloc(sizeof(t_ast *) * ast_node->nb_children);
	if (!ast_node->children)
		return ;
	ast_node->children[0]
		= ((t_stack *)(data->stack->next->next->content))->ast_node;
	ast_node->children[1] = ((t_stack *)(data->stack->content))->ast_node;
	stack_node->symbol = ft_strdup(rule->left_symbol);
	stack_node->ast_node = ast_node;
	clear_stack_after_reduce(data, rule->nb_items, 0);
	ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
}
