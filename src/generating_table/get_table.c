/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 02:26:54 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/04 02:33:45 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **fill_parsing_table(t_parser *data, char **table)
{

}

char    **create_parsing_table()
{
    t_parser    *data;
    char        **table;
    
    data = malloc(sizeof(t_parser));
    if (!data)
        return (NULL);
    get_rules(data);
    get_symbols(data);
    get_firsts(data);
    get_follows(data);
    table = malloc(sizeof(char *) * (ft_lstsize(data->states) + 1));
    if (!table)
        return (NULL);
    return (fill_parsing_table(data, table));
}