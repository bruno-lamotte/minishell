/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 08:49:43 by user              #+#    #+#             */
/*   Updated: 2026/03/25 15:34:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_export_name(char *str)
{
    int i;

    i = 0;
    if (!str[0] || str[0] == '=' || ft_isdigit(str[0]))
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

t_list	*find_var(t_list *env, char *arg)
{
    int len;
    char    *equal;
    char    *content;

    equal = ft_strchr(arg, '=') ;
    if (equal)
        len = equal - arg;
    else
        len = ft_strlen(arg);
    while (env)
    {
        content = env->content;
        if (ft_strncmp(content, arg, len) == 0
			&& (content[len] == '=' || content[len] == '\0'))
            return (env);
        env = env->next;
    }
    return (NULL);
}

static void add_or_replace(t_shell *shell, char *arg)
{
    t_list  *existing;

    existing = find_var(shell->env, arg);
    if (existing)
    {
        free(existing->content);
        existing->content = ft_strdup(arg);
    }
    else
        ft_lstadd_back(&shell->env, ft_lstnew(ft_strdup(arg)));
}


int builtin_export(t_shell *shell, char **args)
{
    int i;

    i = 1;
    if (!args[i])
    {
        print_export(shell->env);
        return (0);
    }
    while (args[i])
    {
        if (!is_valid_export_name(args[i]))
        {
            ft_printf("minishell: export: '%s': not a valid identifier\n", args[i]);
            shell->exit_code = 1;
        }
        else
            add_or_replace(shell, args[i]);
        i++;
    }
    return (0);
}
