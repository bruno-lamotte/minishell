/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:57:08 by user              #+#    #+#             */
/*   Updated: 2026/03/25 10:32:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_char(char *content)
{
    int i;

    i = 0;
    ft_printf("declare -x ");
    while (content[i] && content[i] != '=')
        i++;
    write (1, content, i);
    if (content[i] == '=')
        ft_printf("=\"%s\"", &content[i + 1]);
    ft_printf("\n");
}

void    print_export(t_list *env)
{
    while (env)
    {
        print_char(env->content);
        env = env->next;
    }
}
