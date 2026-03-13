int parser(int **table, t_list *stack, t_list *tokens)
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
            return (print_parsing_error(table, stack, id, token), 0);
        if (action == ACCEPTED)
            return (1);
        tokens_list = tokens_list->next;
    }
    return (0);
}
