/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:45:50 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/17 05:33:23 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type get_node_type_from_rule(t_rule *rule)
{
    t_list *right_symbols;

    right_symbols = rule->right_symbols;
    if (ft_strnstr(rule->left_symbol, "cmd", ft_strlen(rule->left_symbol)))
        return (COMMAND);
    while (right_symbols)
    {
        if (!ft_strcmp(right_symbol->content, "subshell"))
            return (SUBSHELL);
        if (!ft_strcmp(right_symbol->content, "PIPE"))
            return (PIPE);
        if (!ft_strcmp(right_symbol->content, "SEMI"))
            return (SEQUENCE);
        if (!ft_strcmp(right_symbol->content, "AND_IF"))
            return (AND);
        if (!ft_strcmp(right_symbol->content, "OR_IF"))
            return (OR);
        right_symbols = right_symbols->next;
    }
    return (UNKNOWN);
}

int reduce_booleans(t_parser *data, t_rule *rule, t_node_type node_type)
{
    t_list *right_symbols;

    right_symbols = rule->right_symbols;
    while (right_symbols)
    {
        if (!ft_strcmp(right_symbol->content, "BANG"))
        {
            (t_stack *)(data->stack->content)->ast_node->is_bang = 1;
            return (1);
        }
        if (!ft_strcmp(right_symbol->content, "BACKGROUND"))
        {
            (t_stack *)(data->stack->content)->ast_node->is_async = 1;
            return (1);
        }
        right_symbols = right_symbols->next;
    }
    return (0);
}

t_rule  *get_rule_from_id(t_parser *data, int id)
{
    t_list *rules;

    rules = data->rules;
    while (rules)
    {
        if (((t_rule *)(rules->content))->id == id)
            return ((t_rule *)(rules->content));
        rules = rules->next;
    }
    return (NULL);
}

int is_node_already_type(t_parser *data, int lookahead, t_node_type node_type)
{
    t_list *stack;

    stack = data->stack;
    while (lookahead--)
        stack = stack->next;
    return ((t_stack *)(stack->content)->ast_node->type == node_type);
}

int get_next_state_after_reduce(t_parser *data, int **table, t_rule *rule)
{
    int state_id;

    state_id = (t_stack *)(data->stack->next->content)->state_id;
    return (table[state_id][rule->left_symbol]);
}

int get_size_of_args(t_parser *data, int lookahead)
{
    int size;
    t_list *stack;

    size = 0;
    stack = data->stack;
    while (lookahead--)
    {
        if (((t_stack *)(stack->content))->ast_node)
            size += ((t_stack *)(stack->content))->ast_node->nb_args;
        else
            size += ((t_stack *)(stack->content))->nb_values;
        stack = stack->next;
    }
    return (size);
}

char    **pop_args_from_stack(t_parser *data, int size)
{
    char    **args;
    t_list  *stack;

    stack = data->stack;
    args = malloc(sizeof(char *) * (size + 1));
    if (!args)
        return (NULL/*JSP*/);
    args[size] = NULL;
    while (size--)
    {
        if (((t_stack *)(stack->content))->ast_node)
        {
            size -= ((t_stack *)(stack->content))->ast_node->nb_args;
            ft_memcpy(args + size, ((t_stack *)(stack->content))->ast_node->args, sizeof(char *) * ((t_stack *)(stack->content))->ast_node->nb_args);
        }
        else
        {
            size -= ((t_stack *)(stack->content))->ast_node->nb_args;
            ft_memcpy(args + size, ((t_stack *)(stack->content))->values, sizeof(char *) * ((t_stack *)(stack->content))->nb_values);
        }
        stack = stack->next;
    }
    return (args);
}

int is_redirection_symbol(t_token *token)
{
    return (!ft_strcmp(token->type, "redirect_list")
        || !ft_strcmp(token->type, "io_redirect"));
}

t_list  *get_redirection_from_symbol(t_stack *stack)
{
    int i;
    t_redirection *new_redir;
    t_list *list_redirs;

    
    list_redirs = malloc(sizeof(t_redirection));
    if (!list_redirs)
        return (NULL/*JSP*/);
    i = 0;
    while (i < stack->nb_values)
    {
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (NULL/*JSP*/);
        new_redir->file = ft_strdup(((t_stack *)(stack->content))->symbol);
        if (!ft_strcmp(stack->values[i], "<"))
            new_redir->type = INPUT;
        if (!ft_strcmp(stack->values[i], ">"))
            new_redir->type = OUTPUT;
        if (!ft_strcmp(stack->values[i], ">>"))
            new_redir->type = APPEND;
        if (!ft_strcmp(stack->values[i], "<<"))
            new_redir->type = HEREDOC;
        ft_lstadd_back(&list_redirs, ft_lstnew(new_redir));
        i++;
    }
    return (list_redirs);
}

t_list  *pop_redirections_from_stack(t_parser *data, int lookahead)
{
    t_list          *redirections;
    t_list          *new_redir;
    t_list          *stack;

    redirections = NULL;
    stack = data->stack;
    while (lookahead--)
    {
        if (((t_stack *)(stack->content))->ast_node)
            ft_lstadd_back(&redirections, ((t_stack *)(stack->content))->ast_node->redirections);
        else if (is_redirection_symbol(((t_stack *)(stack->content))->symbol))
        {
            new_redir = get_redirection_from_symbol((t_stack *)(stack->content));
            if (!new_redir)
                return (NULL/*JSP*/);
            ft_lstadd_front(&redirections, new_redirs);
        }
        stack = stack->next;
    }
    return (redirections);
}

void    free_char_array(char **array, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void    clear_stack_after_reduce(t_parser *data, int nb_items, int should_free_ast)
{
    t_list *stack;

    while (nb_items--)
    {
        stack = data->stack;
        data->stack = stack->next;
        if (should_free_ast)
        {
            if ((t_stack *)(stack->content)->ast_node && (t_stack *)(stack->content)->ast_node->type == COMMAND)
            {
                free_char_array(((t_stack *)(stack->content))->ast_node->args, ((t_stack *)(stack->content))->ast_node->nb_args);
                ft_lstclear(&((t_stack *)(stack->content))->ast_node->redirections, NULL);
            }
            free((t_stack *)(stack->content)->ast_node);
        }
        if ((t_stack *)(stack->content)->symbol)
            free_char_array(((t_stack *)(stack->content))->values, ((t_stack *)(stack->content))->nb_values);
        free((t_stack *)(stack->content));
    }
}

void    reduce_ast_command(t_parser *data, t_rule *rule, t_node_type node_type)
{
    t_ast   *ast_node;
    t_stack *stack_node;
    int     lookahead;
    
    lookahead = rule->nb_items;
    stack_node = malloc(sizeof(t_stack));
    if (!stack_node)
        return /*a completer*/;
    ast_node = malloc(sizeof(t_ast));
    if (!ast_node)
        return /*a completer*/;
    ft_bzero(ast_node, sizeof(t_ast));
    ast_node->type = node_type;
    ast_node->nb_args = get_size_of_args(data, lookahead);
    ast_node->args = pop_args_from_stack(data, ast_node->nb_args);
    ast_node->redirections = pop_redirections_from_stack(data, lookahead);
    clear_stack_after_reduce(data, lookahead, 1);
    ft_bzero(stack_node, sizeof(t_stack));
    stack_node->ast_node = ast_node;
    stack_node->symbol = ft_strdup(rule->left_symbol);
    ft_lstadd_front(&((t_stack *)(data->stack->content)->ast_node), ft_lstnew(stack_node));
}

void    reduce_symbol(t_parser *data, t_rule *rule)
{
    t_stack *stack_node;

    stack_node = malloc(sizeof(t_stack));
    if (!stack_node)
        return /*a completer*/;
    ft_bzero(stack_node, sizeof(t_stack));
    stack_node->symbol = ft_strdup(rule->left_symbol);
    stack_node->nb_values = get_size_of_args(data, rule->nb_items);
    stack_node->values = pop_args_from_stack(data, stack_node->nb_values);
    clear_stack_after_reduce(data, rule->nb_items, 0);
    ft_lstadd_front(&((t_stack *)(data->stack->content)->ast_node), ft_lstnew(stack_node));
}

void    reduce_ast_subshell(t_parser *data, t_rule *rule, t_node_type node_type)
{
    t_ast   *ast_node;
    t_list  *tmp_list;
    t_stack *stack_node;
    
    if (rule->nb_items == 2)
    {
        tmp_list = ((t_stack *)(data->stack->content))->ast_node->redirections;
        ((t_stack *)(data->stack->content))->ast_node->redirections = pop_redirections_from_stack(data, rule->nb_items);
        ft_lstclear(&tmp_list, NULL);
        (t_stack *)(data->stack->content)->symbol = ft_strdup(rule->left_symbol);
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
        ft_lstadd_front(&((t_stack *)(data->stack->content)->ast_node), ft_lstnew(stack_node));
    }
}

void    reduce_multiple_pipes(t_parser *data, t_rule *rule)
{
    t_ast   *ast_node;
    t_list  *stack_node_to_update;
    t_stack *stack_node;
    t_ast   **children;
    int     i;
    
    i = 0;
    stack_node_to_update = data->stack;
    while (i++ < rule->nb_items)
        stack_node_to_update = stack_node_to_update->next;
    stack_node = stack_node_to_update->content;
    children = malloc(sizeof(t_ast *) * stack_node->ast_node->nb_children + 2);
    ft_memmove(children, stack_node->ast_node->children, sizeof(t_ast *) * stack_node->ast_node->nb_children);
    children[stack_node->ast_node->nb_children] = ((t_stack *)(data->stack->content))->ast_node;
    stack_node->symbol = ft_strdup(rule->left_symbol);
    clear_stack_after_reduce(data, rule->nb_items - 1, 0);
    ft_lstadd_front(&((t_stack *)(data->stack->content)->ast_node), ft_lstnew(stack_node));
}

void    reduce_ast_control(t_parser *data, t_rule *rule, t_node_type node_type)
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
    ast_node->children = malloc(sizeof(t_ast *) * ast_node->nb_children + 1);
    if (!ast_node->children)
        return /*a completer*/;
    ast_node->children[0] = ((t_stack *)(data->stack->next->next->content))->ast_node;
    ast_node->children[1] = ((t_stack *)(data->stack->content))->ast_node;
    stack_node->symbol = ft_strdup(rule->left_symbol);
    stack_node->ast_node = ast_node;
    clear_stack_after_reduce(data, rule->nb_items, 0);
    ft_lstadd_front(&((t_stack *)(data->stack->content)->ast_node), ft_lstnew(stack_node));
}

void    reduce(t_parser *data, int **table, int action)
{
    t_rule      *rule;
    t_node_type node_type;

    rule = get_rule_from_id(data, -action);
    node_type = get_node_type_from_rule(rule);
    if (node_type == COMMAND)
        reduce_ast_command(data, rule, node_type);
    else if (node_type == SUBSHELL 
        || ft_strnstr(rule->left_symbol, "subshell", ft_strlen(rule->left_symbol)))
        reduce_ast_subshell(data, rule, node_type);
    else if (node_type == PIPE && is_node_already_type(data, rule->nb_items, node_type))
        reduce_multiple_pipes(data, rule);
    else if (node_type == PIPE || node_type == SEQUENCE || node_type == AND || node_type == OR)
        reduce_ast_control(data, rule, node_type);
    else if (!reduce_booleans(data, rule, node_type))
        reduce_symbol(data, rule);
    (t_stack *)(data->stack->content)->state_id = get_next_state_after_reduce(data, table, rule);
}
