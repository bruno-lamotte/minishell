/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:36:01 by marvin            #+#    #+#             */
/*   Updated: 2026/03/20 00:36:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_table(int **table, t_parser *data)
{
    int     i;
    t_list  *sym;
    int     j;
    int     nb_sym;

    nb_sym = ft_lstsize(data->symbols);
    printf("%-6s|", "ETAT");
    sym = data->symbols;
    while (sym)
    {
        printf(" %-16s|", ((t_symbol *)sym->content)->name);
        sym = sym->next;
    }
    printf("\n");
    i = 0;
    while (table[i])
    {
        printf("%-6d|", i);
        j = 0;
        while (j < nb_sym)
        {
            if (table[i][j] == ACCEPTED)
                printf(" %-16s|", "ACC");
            else if (table[i][j] == 0)
                 printf(" %-16s|", ".");
            else
                printf(" %-16d|", table[i][j]);
            j++;  
        }
        printf("\n");
        i++;
    }
}

void set_row(int **table, int state_index, char *values)
{
    char    **split;
    int     i;

    split = ft_split(values, ' ');
    if (!split)
        return ;
    i = 0;
    while (split[i])
    {
        table[state_index][i] = ft_atoi(split[i]);
        free(split[i]);
        i++;
    }
    free(split);
}

void    print_table_in_c(int **table, int nb_states, int nb_tokens)
{
    int i;
    int j;

    printf("#include \"minishell.h\"\n\n");
    i = 0;
    while (i < nb_states)
    {
        if (i % 12 == 0)
        {
            if (i != 0)
                printf("}\n\n");
            printf("void\tinit_table_part_%d(int **t)\n{\n", i / 12);
        }
        printf("\tset_row(t, %d, \"", i);
        j = 0;
        while (j < nb_tokens)
        {
            printf("%d", table[i][j]);
            if (j < nb_tokens - 1)
                printf(" ");
            if ((j + 1) % 20 == 0 && j < nb_tokens - 1)
                printf("\"\n\t\t\"");
            j++;
        }
        printf("\");\n");
        i++;
    }
    if (nb_states > 0)
        printf("}\n");
}

void    print_rules_in_c(t_list *rules_list)
{
    t_rule  *rule;
    int     i;

    i = 0;
    while (rules_list)
    {
        rule = (t_rule *)rules_list->content;
        if (i % 12 == 0)
        {
            if (i != 0)
                printf("}\n\n");
            printf("void\tinit_rules_part_%d(t_reduce_rule *rules)\n{\n", i / 12);
        }
        printf("\trules[%d].left_symbol = \"%s\";\n", i, rule->left_symbol);
        printf("\trules[%d].nb_items = %d;\n", i, rule->nb_items);
        rules_list = rules_list->next;
        i++;
    }
    if (i > 0)
        printf("}\n");
}
