/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:43:31 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 18:49:53 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_table_data(t_parser *data)
{
	int	i;

	data->table = malloc(sizeof(int *) * 57);
	i = 0;
	while (i < 57)
	{
		data->table[i] = ft_calloc(34, sizeof(int));
		i++;
	}
	data->rules = malloc(sizeof(t_reduce_rule) * 43);
	data->symbols = malloc(sizeof(char *) * 35);
	ft_bzero(data->symbols, sizeof(char *) * 35);
	init_table_part_0(data->table);
	init_rules_part_0(data->rules);
	init_symbols_part_0(data->symbols);
}

static void	init_stack(t_parser *data)
{
	t_stack	*stack;

	stack = ft_calloc(1, sizeof(t_stack));
	if (!stack)
		return ;
	ft_lstadd_front(&data->stack, ft_lstnew(stack));
}

void	set_row(int **table, int state_index, char *values)
{
	char	**split;
	int		i;

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

t_parser	init_parser_data(void)
{
	t_parser	data;

	ft_bzero(&data, sizeof(t_parser));
	init_table_data(&data);
	init_stack(&data);
	return (data);
}
