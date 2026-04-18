/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 20:32:21 by blamotte          #+#    #+#             */
/*   Updated: 2026/04/11 00:09:33 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_end_of_imput(char c)
{
	return (c == '\0' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';'
		|| c == '&' || c == '(' || c == ')' || c == '!');
}

int	can_be_added_to_opperator(char c)
{
	return (c == '<' || c == '>' || c == '&' || c == '|');
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	handle_comment(char *str, int *i)
{
	if (str[*i] == '#')
	{
		while (str[*i] && str[*i] != '\n')
			(*i)++;
		return (1);
	}
	return (0);
}
