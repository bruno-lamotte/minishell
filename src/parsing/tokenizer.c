/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:52:12 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 20:06:31 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *make_token(char *str, int i, char *type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL/*JSP*/); 
    token->type = ft_strdup(type);
    token->value = ft_substr(str, 0, i);
    return (token);
}

int handle_is_operator(char *str, int *i)
{
    if (*i != 0)
        return (0);
    if (!is_operator(str[*i]))
        return (0);
    (*i)++;
    while (can_be_added_to_opperator(str[*i]))
        (*i)++;
    return (1);
}

t_token *tokenizer_loop(char **str)
{
    int    i;
    int    quoted;

    while (is_blank(**str))
        (*str)++;
    i = 0;
    quoted = 0;
    while(1)
    {
        if (is_quote((*str)[i]))
            quoted = !quoted;
        if (is_end_of_imput((*str)[i]))
        {
            if (quoted && (*str)[i] == '\n')
                i++;
            else if (quoted)
                return (NULL);
            if (i == 0)
                return (make_token(*str, i, "$"));
            else
                return (make_token(*str, i, "WORD"));
        }
    //    handle_comment(str, &i);
        if (handle_is_operator(*str, &i))
            return (make_token(*str, i, "OPERATOR"));
        if (!quoted && is_blank((*str)[i]))
            return (make_token(*str, i, "WORD"));
        i++;
    }
}

t_list *tokenizer(char *str)
{
    t_token *token;
    t_list  *tokens_list;

    tokens_list = NULL;
    while (1)
    {
        token = tokenizer_loop(&str);
        ft_lstadd_back(&tokens_list, ft_lstnew(token));
        if (!token || !ft_strcmp(token->type, "$"))
            break ;
        str += ft_strlen(token->value);
    }
    return (tokens_list);
}
