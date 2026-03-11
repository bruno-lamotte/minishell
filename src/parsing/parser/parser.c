int parser(int **table, t_stack *stack, t_list *tokens)
{
    int action;
    t_token token;

    while (token)
    {
        token = tokens->content;
        action = table[stack->content->state_id][token];
        if (action == ACCEPTED)
            return (1);
        token = tokens->next;
    }
    return (0);
}
