/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:52:12 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/15 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*tokenize_operator(char *str, int *i)
{
	if (str[*i] == '|')
		return ((*i)++, create_token(ft_strdup("|"), TOKEN_PIPE));
	if (str[*i] == '>' && str[*i + 1] == '>')
		return ((*i) += 2, create_token(ft_strdup(">>"), TOKEN_DGREAT));
	if (str[*i] == '>')
		return ((*i)++, create_token(ft_strdup(">"), TOKEN_RET_TO));
	if (str[*i] == '<' && str[*i + 1] == '<')
		return ((*i) += 2, create_token(ft_strdup("<<"), TOKEN_DLESS));
	if (str[*i] == '<')
		return ((*i)++, create_token(ft_strdup("<"), TOKEN_RET_FROM));
	return (NULL);
}

static t_token	*tokenize_word(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && !is_blank(str[*i]) && !is_operator_char(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
			*i = skip_quotes(str, *i);
		else
			(*i)++;
	}
	return (create_token(ft_substr(str, start, *i - start), TOKEN_WORD));
}

t_list	*tokenize(char *str)
{
	t_list	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_blank(str[i]))
			i++;
		if (!str[i])
			break ;
		if (is_operator_char(str[i]))
			token = tokenize_operator(str, &i);
		else
			token = tokenize_word(str, &i);
		if (!token)
			return (NULL);
		ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	ft_lstadd_back(&tokens, ft_lstnew(create_token(ft_strdup("$"), TOKEN_END)));
	return (tokens);
}
