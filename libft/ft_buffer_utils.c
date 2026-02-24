/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:33:14 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 02:34:25 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flush(t_data *list)
{
	if (list->index_buffer > 0)
		write(1, list->buffer, list->index_buffer);
	list->index_buffer = 0;
}

void	ft_putchar_buffer(char c, t_data *list)
{
	if (list->index_buffer == BUFFER_SIZE)
		ft_flush(list);
	list->buffer[list->index_buffer] = c;
	list->index_buffer++;
	list->len++;
}

void	ft_putstr_buffer(char *str, t_data *list)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_putchar_buffer(str[i], list);
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
