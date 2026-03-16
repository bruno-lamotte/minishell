/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:25:07 by marvin            #+#    #+#             */
/*   Updated: 2026/03/13 20:51:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shift(t_list *stack, int state_id, t_token token)
{
    t_stack *new_node;

    new_node = malloc(sizeof(t_stack));
    if (!new_node)
        return /*a completer*/;
    ft_bzero(new_node->ast_node, sizeof(t_ast));
    new_node->state_id = state_id;
    new_node->ast_node->args = malloc(sizeof(char *) * 2);
    if (!new_node->ast_node->args)
        return /*a completer*/;
    new_node->ast_node->args[0] = ft_strdup(token);
    if (!new_node->ast_node->args[0])
        return /*a completer*/;
    new_node->ast_node->args[1] = NULL;
    new_node->ast_node->type = STRING;
    ft_lstadd_front(&stack, ft_lstnew(new_node));
}

void    create_ast_node_from_rule(t_ast **ast_node, t_rule *rule, t_list *stack)
{
    int i;
    int j;
    int k;
    t_stack *tmp_stack;
    char **tmp_args;

    (*ast_node)->type = get_node_type_from_symbol(rule->left_symbol);
    (*ast_node)->args = malloc(sizeof(char *) * (rule->nb_items + 1));
    if (!(*ast_node)->args)
        return /*a completer*/;
    i = rule->nb_items;
    k = 0;
    while (i)
    {
        tmp_stack = (t_stack *)(stack->content);
        while (tmp_stack->args[j])
            (*ast_node)->args[i] = ft_strdup((char *)stack);
        if (!(*ast_node)->args[i])
            return /*a completer*/;
        i--;
    }
    (*ast_node)->args[i] = NULL;
}

void    reduce(t_parser *data, t_list *stack, int **table, int action)
{
    t_rule  *rule;
    t_new_node *tmp_node;
    
    rule = get_rule_from_id(data, action);
    tmp_node = create_node_from_rule(rule, stack);
    
}

int parser(t_parser *data, int **table, t_list *stack, t_list *tokens)
{
    int     action;
    int     id;
    t_list *tokens_list;
    t_token token;

    tokens_list = tokens;
    while (tokens_list)
    {
        token = tokens_list->content;
        id = (t_stack *)(stack->content)->state_id;
        action = table[id][token];
        if (!action)
            return (print_parsing_error(data, table, id, token), 0);
        else if (action == ACCEPTED)
            return (1);
        else if (action < 0)
            reduce(data, stack, table, -action);
        else
        {
            shift(stack, action, token);
            tokens_list = tokens_list->next;
        }
    }
    return (0);
}
