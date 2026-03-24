/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:25:07 by marvin            #+#    #+#             */
/*   Updated: 2026/03/24 21:04:08 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shift(t_parser *data, int state_id, t_token *token)
{
    t_stack *new_node;

    new_node = malloc(sizeof(t_stack));
    if (!new_node)
        return /*a completer*/;
    new_node->state_id = state_id;
    printf("Shift to state %d with token \"%s\" of type \"%s\"\n", state_id, token->value, token->type);
    new_node->ast_node = NULL;
    new_node->symbol = ft_strdup(token->type);
    new_node->values = malloc(sizeof(char *) * 2);
    if (!new_node->symbol || !new_node->values)
        return /*a completer*/;
    new_node->values[0] = ft_strdup(token->value);
    if (!new_node->symbol || !new_node->values)
        return /*a completer*/;
    new_node->nb_values = 1;
    ft_lstadd_front(&data->stack, ft_lstnew(new_node));
}

void    reduce(t_parser *data, int **table, int action)
{
    t_reduce_rule  *rule;
    t_node_type     node_type;

    rule = &data->rules[action];
    printf("Reduce using rule %d : %s\n", -action, rule->left_symbol);
    node_type = get_node_type_from_rule(rule, data->stack);
    if (node_type == COMMAND)
        reduce_ast_command(data, rule, node_type);
    else if (node_type == SUBSHELL 
        || ft_strnstr(rule->left_symbol, "subshell", ft_strlen(rule->left_symbol)))
        reduce_ast_subshell(data, rule, node_type);
    else if (node_type == PIPE && is_node_already_type(data, rule->nb_items, node_type))
        reduce_multiple_pipes(data, rule);
    else if (node_type == PIPE || node_type == SEQUENCE || node_type == AND || node_type == OR)
        reduce_ast_control(data, rule, node_type);
    else if (!reduce_booleans(data, rule))
        reduce_symbol(data, rule);
    ((t_stack *)(data->stack->content))->state_id = get_next_state_after_reduce(data, table, rule);
}

void    print_parsing_error(t_parser *data, int **table, int id, t_token *token)
{
    int     i;
    char    **symbols;

    printf("Parsing error at token \"%s\" of type \"%s\"", token->value, token->type);
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

int parser(t_parser *data)
{
    int     action;
    int     id;
    t_list *tokens_list;
    t_token *token;

    tokens_list = data->tokens;
    while (tokens_list)
    {
        id = ((t_stack *)(data->stack->content))->state_id;
        token = lex_token(data, data->table, ((t_token *)(tokens_list->content)), id);
        if (!token)
            return (print_parsing_error(data, data->table, id, token), 0);
        action = data->table[id][get_symbol_nbr(data, token->type)];
        if (!action)
            return (print_parsing_error(data, data->table, id, token), 0);
        else if (action == ACCEPTED)
            return (1);
        else if (action < 0)
            reduce(data, data->table, -action);
        else
        {
            shift(data, action, token);
            tokens_list = tokens_list->next;
        }
    }
    return (0);
}
