/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:57:55 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 18:31:49 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int reduce_booleans(t_parser *data, t_reduce_rule *rule)
{
    t_list *stack;

    stack = data->stack;
    if (ft_strnstr(rule->left_symbol, "pipeline", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol 
        && !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "BANG"))
    {
        ((t_stack *)(stack->content))->ast_node->is_bang = 1;
        return (1);
    }
     if ((ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && ((t_stack *)(stack->next->content))->symbol 
        && !ft_strcmp(((t_stack *)(stack->next->content))->symbol, "BACKGROUND"))
        || (ft_strnstr(rule->left_symbol, "and_or", ft_strlen(rule->left_symbol))
        && rule->nb_items == 3 && ((t_stack *)(stack->content))->symbol 
        && !ft_strcmp(((t_stack *)(stack->content))->symbol, "BACKGROUND")))
    {
        ((t_stack *)(stack->content))->ast_node->is_async = 1;
        return (1);
    }
    return (0);
}

void    reduce_ast_subshell(t_parser *data, t_reduce_rule *rule, t_node_type node_type)
{
    t_ast   *ast_node;
    t_list  *tmp_list;
    t_stack *stack_node;
    
    if (rule->nb_items == 2)
    {
        tmp_list = ((t_stack *)(data->stack->content))->ast_node->redirections;
        ((t_stack *)(data->stack->content))->ast_node->redirections = pop_redirections_from_stack(data, rule->nb_items);
        ft_lstclear(&tmp_list, NULL);
        ((t_stack *)(data->stack->content))->symbol = ft_strdup(rule->left_symbol);
        return ;
    }
    else if (rule->nb_items == 3)
    {
        stack_node = malloc(sizeof(t_stack));
        ft_bzero(stack_node, sizeof(t_stack));
        ast_node = malloc(sizeof(t_ast));
        if (!ast_node || !stack_node)
            return /*a completer*/;
        ft_bzero(ast_node, sizeof(t_ast));
        ast_node->type = node_type;
        ast_node->nb_children = 1;
        ast_node->children = malloc(sizeof(t_ast *) * ast_node->nb_children + 1);
        if (!ast_node->children)
            return /*a completer*/;
        ast_node->children[0] = ((t_stack *)(data->stack->next->content))->ast_node;
        stack_node->symbol = ft_strdup(rule->left_symbol);
        stack_node->ast_node = ast_node;
        clear_stack_after_reduce(data, rule->nb_items, 0);
        ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
    }
}

void    reduce_multiple_pipes(t_parser *data, t_reduce_rule *rule)
{
    t_list  *stack_node_to_update;
    t_stack *stack_node;
    t_ast   **children;
    int     i;
    
    i = 0;
    stack_node_to_update = data->stack;
    while (i++ < rule->nb_items)
        stack_node_to_update = stack_node_to_update->next;
    stack_node = stack_node_to_update->content;
    children = malloc(sizeof(t_ast *) * (stack_node->ast_node->nb_children + 1));
    ft_memmove(children, stack_node->ast_node->children, sizeof(t_ast *) * stack_node->ast_node->nb_children);
    children[stack_node->ast_node->nb_children] = ((t_stack *)(data->stack->content))->ast_node;
    stack_node->symbol = ft_strdup(rule->left_symbol);
    clear_stack_after_reduce(data, rule->nb_items - 1, 0);
}

void    reduce_ast_control(t_parser *data, t_reduce_rule *rule, t_node_type node_type)
{
    t_ast   *ast_node;
    t_stack *stack_node;

    ast_node = malloc(sizeof(t_ast));
    stack_node = malloc(sizeof(t_stack));
    if (!ast_node || !stack_node)
        return /*a completer*/;
    ft_bzero(ast_node, sizeof(t_ast));
    ft_bzero(stack_node, sizeof(t_stack));
    ast_node->type = node_type;
    ast_node->nb_children = 2;
    ast_node->children = malloc(sizeof(t_ast *) * (ast_node->nb_children));
    if (!ast_node->children)
        return /*a completer*/;
    ast_node->children[0] = ((t_stack *)(data->stack->next->next->content))->ast_node;
    ast_node->children[1] = ((t_stack *)(data->stack->content))->ast_node;
    stack_node->symbol = ft_strdup(rule->left_symbol);
    stack_node->ast_node = ast_node;
    clear_stack_after_reduce(data, rule->nb_items, 0);
    ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
}

void    reduce_symbol(t_parser *data, t_reduce_rule *rule)
{
    t_stack *stack_node;
    t_ast   *ast;

    stack_node = malloc(sizeof(t_stack));
    if (!stack_node)
        return ;
    ft_bzero(stack_node, sizeof(t_stack));
    stack_node->symbol = ft_strdup(rule->left_symbol);
    ast = ((t_stack *)(data->stack->content))->ast_node;
    if (rule->nb_items == 1 && ast)
    {
        stack_node->ast_node = ast;
        ((t_stack *)(data->stack->content))->ast_node = NULL;
        clear_stack_after_reduce(data, 1, 0);
    }
    else if (rule->nb_items == 2 && ast
        && ((t_stack *)(data->stack->next->content))->symbol
        && !ft_strcmp(((t_stack *)(data->stack->next->content))->symbol, "BANG"))
    {
        stack_node->ast_node = ast;
        stack_node->ast_node->is_bang = !stack_node->ast_node->is_bang;
        ((t_stack *)(data->stack->content))->ast_node = NULL;
        clear_stack_after_reduce(data, 2, 0);
    }
    else
    {
        stack_node->nb_values = get_size_of_args(data, rule->nb_items);
        stack_node->values = pop_args_from_stack(data, stack_node->nb_values);
        clear_stack_after_reduce(data, rule->nb_items, 0);
    }
    ft_lstadd_front(&data->stack, ft_lstnew(stack_node));
}
