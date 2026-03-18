/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:58:26 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/18 06:58:32 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_name(char *str, int len)
{
    int i;

    if (!str || !len || ft_isdigit(str[0]))
        return (0);
    i = 0;
    while (i < len)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

t_token lex_assignment(int **table, t_token *token, int state_id)
{
    char    *first_quote;
    char    *equal;
    
    first_quote = ft_strchr(token->value, '"');
    equal = ft_strchr(token->value, '=');
    if (equal && (!first_quote || equal < first_quote) 
        && table[state_id][ASSIGNMENT_WORD]
        && !ft_strcmp(token->type, "WORD")
        && is_valid_name(token->value, equal - token->value))
        token->type = "ASSIGNMENT_WORD";
    return (token);
}
