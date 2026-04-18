/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:28:16 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 09:04:08 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_command_node(t_stack *node)
{
	free_char_array(node->ast_node->args, node->ast_node->nb_args);
	free_char_array(node->ast_node->assignments,
		node->ast_node->nb_assignments);
	ft_lstclear(&node->ast_node->redirections, NULL);
}

static void	free_stack_content(t_stack *node, int should_free_ast)
{
	if (should_free_ast && node->ast_node)
	{
		if (node->ast_node->type == COMMAND)
			free_command_node(node);
		free(node->ast_node);
	}
	if (node->values)
		free_char_array(node->values, node->nb_values);
	free(node->symbol);
	free(node);
}

void	clear_stack_after_reduce(t_parser *data, int nb_items,
		int should_free_ast)
{
	t_list	*stack;

	while (nb_items--)
	{
		stack = data->stack;
		data->stack = stack->next;
		free_stack_content(stack->content, should_free_ast);
		free(stack);
	}
}
