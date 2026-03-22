/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:58:26 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/22 22:20:22 by marvin           ###   ########.fr       */
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
    if (ft_strchr(token->value, '\'') && (!first_quote || ft_strchr(token->value, '\'') < first_quote))
        first_quote = ft_strchr(token->value, '\'');
    equal = ft_strchr(token->value, '=');
    if (equal && (!first_quote || equal < first_quote) 
        && table[state_id][ASSIGNMENT_WORD]
        && !ft_strcmp(token->type, "WORD")
        && is_valid_name(token->value, equal - token->value))
        token->type = "ASSIGNMENT_WORD";
    return (token);
}

t_token	    *lex_operator(t_token *token)
{
    if (!ft_strcmp(token->value, "|"))
        token->type = "PIPE";
    else if (!ft_strcmp(token->value, "<"))
        token->type = "INPUT_REDIRECT";
    else if (!ft_strcmp(token->value, ">"))
        token->type = "OUTPUT_REDIRECT";
    else if (!ft_strcmp(token->value, ">>"))
        token->type = "APPEND_REDIRECT";
    else if (!ft_strcmp(token->value, "<<"))
        token->type = "HEREDOC_REDIRECT";
    else if (!ft_strcmp(token->value, "&"))
        token->type = "BACKGROUND";
    else if (!ft_strcmp(token->value, ";"))
        token->type = "SEMICOLON";
    else if (!ft_strcmp(token->value, "&&"))
        token->type = "AND_IF";
    else if (!ft_strcmp(token->value, "||"))
        token->type = "OR_IF";
    return (token);
}

t_token *lex_token(int **table, t_token *token, int state_id)
{
    if (!token)
        return (NULL);
    if (token->type && !ft_strcmp(token->type, "WORD"))
        return (lex_assignment(table, token, state_id));
    if (token->type && !ft_strcmp(token->type, "OPERATOR"))
        return (lex_operator(token));
    return (token);
}
