/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_cmd_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_stack_values(t_stack *node)
{
	free(node->values);
	node->values = NULL;
	node->nb_values = 0;
}

static void	copy_ast_assignments(char **assignments, t_stack *node, int *size)
{
	*size -= node->ast_node->nb_assignments;
	ft_memcpy(assignments + *size, node->ast_node->assignments,
		sizeof(char *) * node->ast_node->nb_assignments);
	free(node->ast_node->assignments);
	node->ast_node->assignments = NULL;
	node->ast_node->nb_assignments = 0;
	clear_stack_values(node);
}

char	**pop_assignements_from_stack(t_parser *data, int size)
{
	char	**assignments;
	t_list	*stack;

	if (size == 0)
		return (NULL);
	assignments = malloc(sizeof(char *) * (size + 1));
	if (!assignments)
		return (NULL);
	assignments[size] = NULL;
	stack = data->stack;
	while (size)
	{
		if (((t_stack *)(stack->content))->ast_node)
			copy_ast_assignments(assignments, stack->content, &size);
		else if (!ft_strcmp(((t_stack *)(stack->content))->symbol,
			"ASSIGNMENT_WORD"))
		{
			size--;
			assignments[size] = ft_strdup(((t_stack *)(stack->content))
					->values[0]);
			clear_stack_values(stack->content);
		}
		stack = stack->next;
	}
	return (assignments);
}

static void	copy_ast_args(char **args, t_stack *node, int *size)
{
	*size -= node->ast_node->nb_args;
	ft_memcpy(args + *size, node->ast_node->args,
		sizeof(char *) * node->ast_node->nb_args);
	free(node->ast_node->args);
	node->ast_node->args = NULL;
	node->ast_node->nb_args = 0;
	clear_stack_values(node);
}

char	**pop_args_from_stack(t_parser *data, int size)
{
	char	**args;
	t_list	*stack;

	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	args[size] = NULL;
	stack = data->stack;
	while (size)
	{
		if (((t_stack *)(stack->content))->ast_node)
			copy_ast_args(args, stack->content, &size);
		else if (!is_redirection_symbol((t_stack *)(stack->content))
			&& ft_strcmp(((t_stack *)(stack->content))->symbol,
			"ASSIGNMENT_WORD"))
		{
			size -= ((t_stack *)(stack->content))->nb_values;
			ft_memcpy(args + size, ((t_stack *)(stack->content))->values,
				sizeof(char *) * ((t_stack *)(stack->content))->nb_values);
			clear_stack_values(stack->content);
		}
		stack = stack->next;
	}
	return (args);
}
