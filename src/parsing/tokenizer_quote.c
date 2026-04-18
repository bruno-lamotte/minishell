/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:19:43 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 13:37:29 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_quote(char c)
{
	static int	quotes[256];

	if (!quotes[(unsigned char)c])
		quotes[(unsigned char)c] = (c == '"' || c == '\'');
	return (quotes[(unsigned char)c]);
}
