/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:47:23 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 02:48:06 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_list(t_data *list)
{
	list->width = 0;
	list->precision = 0;
	list->zero = 0;
	list->point = 0;
	list->dash = 0;
	list->plus = 0;
	list->space = 0;
	list->hash = 0;
}

int	ft_printf(const char *s, ...)
{
	t_data	list;

	list.index_buffer = 0;
	list.len = 0;
	if (!s)
		return (-1);
	va_start(list.args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			ft_reset_list(&list);
			s = parsing_s(s, &list);
		}
		else
		{
			ft_putchar_buffer(*s, &list);
			s++;
		}
	}
	ft_flush(&list);
	va_end(list.args);
	return (list.len);
}
