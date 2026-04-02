#include "minishell.h"

static void	free_item(void *content)
{
    if (!content)
        return ;
    free(content);
}

static void	free_transition(void *content)
{
    t_transition	*transition;

    if (!content)
        return ;
    transition = (t_transition *)content;
    free(transition->symbol);
    free(transition);
}

void    free_states(t_list *states)
{
    t_list  *current;
    t_state *state;

    current = states;
    while (current)
    {
        state = (t_state *)current->content;
        ft_lstclear(&state->items, free_item);
        ft_lstclear(&state->transitions, free_transition);
        free(state);
        current = current->next;
    }
    ft_lstclear(&states, NULL);
}

void    free_symbols(t_list *symbols)
{
    t_list      *current;
    t_symbol    *symbol;
    t_list      *tmp;
    t_list      *prev;

    current = symbols;
    while (current)
    {
        symbol = (t_symbol *)current->content;
        tmp = symbol->firsts;
        prev = NULL;
        while (tmp)
        {
            if (tmp->content == symbol->name)
            {
                if (prev)
                    prev->next = tmp->next;
                else
                    symbol->firsts = tmp->next;
                free(tmp);
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        free(symbol->name);
        ft_lstclear(&symbol->firsts, free);
        ft_lstclear(&symbol->follows, free);
        free(symbol);
        current = current->next;
    }
    ft_lstclear(&symbols, NULL);
}

void    free_rules(t_list *rules)
{
    t_list  *current;
    t_rule  *rule;

    current = rules;
    while (current)
    {
        rule = (t_rule *)current->content;
        free(rule->left_symbol);
        ft_lstclear(&rule->right_symbols, free);
        free(rule);
        current = current->next;
    }
    ft_lstclear(&rules, NULL);
}

void    free_table(int **table)
{
    int i;

    i = 0;
    while (table[i])
    {
        free(table[i]);
        i++;
    }
    free(table);
}

void    free_all(t_slr1 *data, int **table)
{
    free_table(table);
    free_rules(data->rules);
    free_symbols(data->symbols);
    free_states(data->states);
    free(data);
}