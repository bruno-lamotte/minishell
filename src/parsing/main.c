/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:58:26 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 20:18:48 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int main(int ac, char **av)
{
    t_parser    data;
    char        *line;
    int         i;
    
    line = ft_strdup("");
    i = 1;
    while (i < ac)
    {
        char *tmp = line;
        line = ft_strjoin(line, av[i]);
        free(tmp);
        if (i < ac - 1)
        {
            tmp = line;
            line = ft_strjoin(line, " ");
            free(tmp);
        }
        i++;
    }
    ft_bzero(&data, sizeof(t_parser));
    data.table = malloc(sizeof(int *) * 57);
    i = 0;
    while (i < 57)
    {
        data.table[i] = ft_calloc(34, sizeof(int));
        i++;
    }
    data.rules = malloc(sizeof(t_reduce_rule) * 43);
    if (!data.rules)
        return (1);
    data.symbols = malloc(sizeof(char *) * 35);
    if (!data.symbols)
        return (1);
    init_table_part_0(data.table);
    init_rules_part_0(data.rules);
    init_symbols_part_0(data.symbols);
    data.tokens = tokenizer(line);
    data.stack = NULL;
    ft_lstadd_front(&data.stack, ft_lstnew(ft_calloc(sizeof(t_stack), 1)));
    if (parser(&data))
        printf("WEEEEEEEEE\n");
}
