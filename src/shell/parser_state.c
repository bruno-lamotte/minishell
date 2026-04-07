/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
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

static void	push_start_state(t_parser *parser)
{
	t_stack	*stack;

	stack = ft_calloc(1, sizeof(t_stack));
	if (!stack)
		return ;
	ft_lstadd_front(&parser->stack, ft_lstnew(stack));
}

void	reset_parser(t_parser *parser)
{
	ft_lstclear(&parser->tokens, free_token);
	clear_duplicate_asts(parser->stack);
	ft_lstclear(&parser->stack, free_stack_node);
	clear_list_nodes(&parser->here_docs);
	parser->tokens = NULL;
	parser->stack = NULL;
	parser->here_docs = NULL;
	push_start_state(parser);
}
