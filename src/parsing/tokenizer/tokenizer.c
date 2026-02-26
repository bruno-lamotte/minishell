/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:52:12 by blamotte          #+#    #+#             */
/*   Updated: 2026/02/27 12:16:32 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token make_token(char *str, int i)

int is_end_of_imput(char c)
{
    return (c == '\0' || c == '\n');
}

int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == ';');
}

int can_be_added_to_opperator(char c)
{
    return (c == '<' || c == '>');
}

int is_blank(char c)
{
    return (c == ' ' || c == '\t');
}

int handle_comment(char *str, int *i)
{
    if (str[*i] == '#')
    {
        while (str[*i] && str[*i] != '\n')
            (*i)++;
        return (1);
    }
    return (0);
}

int handle_previus_is_operator(char *str, int *i)
{
    if (*i == 0)
        return (0);
    if (!is_operator(str[*i - 1]))
        return (0);
    if (!is_operator(str[*i]))
        return (1);
    while (can_be_added_to_opperator(str[*i]))
        (*i)++;
    return (1);
}

int handle_quote_and_backslash(char *str, int i)

int handle_dollar_and_accent(char *str, int i)

t_token tokenizer(char *str)
{
    int     i;

    while (is_blank(*str))
        str++;
    i = 0;
    while(1)
    {
        if (is_end_of_imput(str[i]))
            return (make_token(str, i));
        handle_comment(str, &i);
        if (handle_previus_is_operator(str, &i))
            return (make_token(str, i));
        if (handle_quote_and_backslash(str, &i))
            return (make_token(str, i));
        if (handle_dollar_and_accent(str, &i))
            return (make_token(str, i));
        if (is_operator(str[i]) && i > 0)
            return (make_token(str, i - 1));
        if (is_blank(str[i]))
            return (make_token(str, i - 1));
        i++;
    }
}
 