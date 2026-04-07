/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_duplicate_asts(t_list *stack)
{
	t_ast	*ast;
	t_list	*next;

	while (stack)
	{
		ast = ((t_stack *)stack->content)->ast_node;
		next = stack->next;
		while (ast && next)
		{
			if (((t_stack *)next->content)->ast_node == ast)
				((t_stack *)next->content)->ast_node = NULL;
			next = next->next;
		}
		stack = stack->next;
	}
}

void	free_env_list(t_list **env)
{
	ft_lstclear(env, free_string);
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < node->nb_children)
	{
		free_ast(node->children[i]);
		i++;
	}
	free(node->children);
	free_char_array(node->args, node->nb_args);
	free_char_array(node->assignments, node->nb_assignments);
	ft_lstclear(&node->redirections, free_redirection);
	free(node);
}

void	free_stack_node(void *content)
{
	t_stack	*stack;

	stack = (t_stack *)content;
	if (!stack)
		return ;
	free(stack->symbol);
	free_char_array(stack->values, stack->nb_values);
	free_ast(stack->ast_node);
	free(stack);
}

void	free_parser_data(t_parser *data)
{
	int	i;

	ft_lstclear(&data->tokens, free_token);
	clear_duplicate_asts(data->stack);
	ft_lstclear(&data->stack, free_stack_node);
	clear_list_nodes(&data->here_docs);
	i = 0;
	while (i < 57)
		free(data->table[i++]);
	free(data->table);
	free(data->rules);
	free(data->symbols);
}
