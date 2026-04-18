/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:25:07 by blamotte          #+#    #+#             */
/*   Updated: 2026/04/11 00:09:49 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_action(t_parser *data, t_token *token, t_list **tokens,
		int row)
{
	int	action;
	int	col;

	col = get_symbol_nbr(data, token->type);
	if (col < 0)
		return (0);
	action = data->table[row][col];
	if (!action)
		return (0);
	if (action == ACCEPTED)
		return (2);
	if (action < 0)
		reduce(data, data->table, -action);
	else
	{
		shift(data, action, token);
		*tokens = (*tokens)->next;
	}
	return (1);
}

void	shift(t_parser *data, int state_id, t_token *token)
{
	t_stack	*new_node;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return ;
	new_node->state_id = state_id;
	new_node->ast_node = NULL;
	new_node->symbol = ft_strdup(token->type);
	new_node->values = malloc(sizeof(char *) * 2);
	if (!new_node->symbol || !new_node->values)
		return ;
	new_node->values[0] = ft_strdup(token->value);
	if (!new_node->symbol || !new_node->values)
		return ;
	new_node->nb_values = 1;
	ft_lstadd_front(&data->stack, ft_lstnew(new_node));
}

void	reduce(t_parser *data, int **table, int action)
{
	t_reduce_rule	*rule;
	t_node_type		node_type;

	rule = &data->rules[action];
	node_type = get_node_type_from_rule(rule, data->stack);
	if (node_type == COMMAND)
		reduce_ast_command(data, rule, node_type);
	else if (node_type == SUBSHELL
		|| ft_strnstr(rule->left_symbol, "subshell",
			ft_strlen(rule->left_symbol)))
		reduce_ast_subshell(data, rule, node_type);
	else if (node_type == PIPE
		&& is_node_already_type(data, rule->nb_items, node_type))
		reduce_multiple_pipes(data, rule);
	else if (node_type == PIPE || node_type == SEQUENCE
		|| node_type == AND || node_type == OR)
		reduce_ast_control(data, rule, node_type);
	else if (!reduce_booleans(data, rule))
		reduce_symbol(data, rule);
	((t_stack *)(data->stack->content))->state_id
		= get_next_state_after_reduce(data, table, rule);
}

void	print_parsing_error(t_parser *data, int **table, int id, t_token *token)
{
	int		i;
	char	**symbols;

	printf("Parsing error at token \"%s\" of type \"%s\"\n",
		token->value, token->type);
	printf("Expected tokens are : ");
	symbols = data->symbols;
	i = 0;
	while (symbols[i])
	{
		if (table[id][i])
			printf("%s ", symbols[i]);
		i++;
	}
	printf("\n");
}

int	parser(t_parser *data)
{
	int		row;
	int		status;
	t_list	*tokens_list;
	t_token	*token;

	tokens_list = data->tokens;
	while (tokens_list)
	{
		row = ((t_stack *)(data->stack->content))->state_id;
		token = lex_token(data, data->table,
				((t_token *)(tokens_list->content)), row);
		if (!token)
			return (0);
		status = apply_action(data, token, &tokens_list, row);
		if (status == 2)
			return (1);
		if (!status)
			return (0);
	}
	return (0);
}
