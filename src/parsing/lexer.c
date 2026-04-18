/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:58:26 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/24 20:04:59 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char *str, int len)
{
	int	i;

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

t_token	*lex_assignment(t_parser *data, int **table, t_token *token,
		int state_id)
{
	char	*first_quote;
	char	*equal;

	first_quote = ft_strchr(token->value, '"');
	if (ft_strchr(token->value, '\'')
		&& (!first_quote || ft_strchr(token->value, '\'') < first_quote))
		first_quote = ft_strchr(token->value, '\'');
	equal = ft_strchr(token->value, '=');
	if (equal && (!first_quote || equal < first_quote)
		&& table[state_id][get_symbol_nbr(data, "ASSIGNMENT_WORD")]
		&& !ft_strcmp(token->type, "WORD")
		&& is_valid_name(token->value, equal - token->value))
		token->type = "ASSIGNMENT_WORD";
	return (token);
}

t_token	*lex_operator(t_token *token)
{
	if (!ft_strcmp(token->value, "|"))
		token->type = "PIPE";
	else if (!ft_strcmp(token->value, "<"))
		token->type = "LESS";
	else if (!ft_strcmp(token->value, ">"))
		token->type = "GREAT";
	else if (!ft_strcmp(token->value, ">>"))
		token->type = "DGREAT";
	else if (!ft_strcmp(token->value, "<<"))
		token->type = "DLESS";
	else if (!ft_strcmp(token->value, "&"))
		token->type = "BACKGROUND";
	else if (!ft_strcmp(token->value, ";"))
		token->type = "SEMI";
	else if (!ft_strcmp(token->value, "&&"))
		token->type = "AND_IF";
	else if (!ft_strcmp(token->value, "||"))
		token->type = "OR_IF";
	else if (!ft_strcmp(token->value, "("))
		token->type = "L_PAREN";
	else if (!ft_strcmp(token->value, ")"))
		token->type = "R_PAREN";
	else if (!ft_strcmp(token->value, "!"))
		token->type = "BANG";
	return (token);
}

t_token	*lex_token(t_parser *data, int **table, t_token *token, int state_id)
{
	if (!token)
		return (NULL);
	if (token->type && !ft_strcmp(token->type, "WORD"))
		return (lex_assignment(data, table, token, state_id));
	if (token->type && !ft_strcmp(token->type, "OPERATOR"))
		return (lex_operator(token));
	return (token);
}
