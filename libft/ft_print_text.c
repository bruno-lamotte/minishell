/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:44:32 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 05:18:41 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(t_data *list)
{
	char	c;

	c = va_arg(list->args, int);
	if (list->width > 1 && !list->dash)
	{
		while (list->width > 1)
		{
			ft_putchar_buffer(' ', list);
			list->width--;
		}
	}
	ft_putchar_buffer(c, list);
	if (list->width > 1 && list->dash)
	{
		while (list->width > 1)
		{
			ft_putchar_buffer(' ', list);
			list->width--;
		}
	}
}

void	ft_print_spaces(int len, t_data *list)
{
	while (list->width > len)
	{
		ft_putchar_buffer(' ', list);
		list->width--;
	}
}

void	ft_print_str(t_data *list)
{
	char	*s;
	int		len;
	int		i;

	s = va_arg(list->args, char *);
	if (!s)
	{
		if (list->point && list->precision < 6)
			s = "";
		else
			s = "(null)";
	}
	len = ft_strlen(s);
	if (list->point && list->precision < len)
		len = list->precision;
	if (list->width > len && !list->dash)
		ft_print_spaces(len, list);
	i = 0;
	while (i < len)
	{
		ft_putchar_buffer(s[i], list);
		i++;
	}
	if (list->width > len && list->dash)
		ft_print_spaces(len, list);
}

void	ft_print_percent(t_data *list)
{
	ft_putchar_buffer('%', list);
}
