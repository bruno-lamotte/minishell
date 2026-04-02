/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:45:09 by user              #+#    #+#             */
/*   Updated: 2026/03/25 19:25:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void remove_var(t_shell *shell, char *arg)
{
    t_list  *current;
    t_list  *prev;

    prev = NULL;
    current = shell->env;
    while (current)
    {
        if (find_var(current, arg) == current)
        {
            if (prev == NULL)
                shell->env = current->next;
            else
                prev->next = current->next;
            ft_lstdelone(current, free);
            return ;
        }
        prev = current;
        current = current->next;
    }
}

int builtin_unset(t_shell *shell, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        remove_var(shell, args[i]);
        i++;
    }
    return (0);
}
