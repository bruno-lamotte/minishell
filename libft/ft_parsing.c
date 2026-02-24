/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:34:54 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 05:23:40 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*parsing_flags(const char *s, t_data *list)
{
	while (*s == '-' || *s == '0' || *s == '#' || *s == ' ' || *s == '+')
	{
		if (*s == '-')
			list->dash = 1;
		if (*s == '0')
			list->zero = 1;
		if (*s == '#')
			list->hash = 1;
		if (*s == ' ')
			list->space = 1;
		if (*s == '+')
			list->plus = 1;
		s++;
	}
	return (s);
}

const char	*parsing_width(const char *s, t_data *list)
{
	list->width = 0;
	while (*s >= '0' && *s <= '9')
		list->width = (list->width * 10) + (*s++ - '0');
	return (s);
}

const char	*parsing_precision(const char *s, t_data *list)
{
	if (*s == '.')
	{
		list->point = 1;
		s++;
		list->precision = 0;
		while (*s >= '0' && *s <= '9')
				list->precision = (list->precision * 10) + (*s++ - '0');
	}
	return (s);
}

const char	*parsing_s(const char *s, t_data *list)
{
	s = parsing_flags(s, list);
	s = parsing_width(s, list);
	s = parsing_precision(s, list);
	if (*s == 'c')
		ft_print_char(list);
	else if (*s == 's')
		ft_print_str(list);
	else if (*s == 'p')
		ft_print_ptr(list);
	else if (*s == 'd' || *s == 'i')
		ft_print_int(list);
	else if (*s == 'u')
		ft_print_unsigned(list);
	else if (*s == 'x' || *s == 'X')
		ft_print_hex(list, *s);
	else if (*s == '%')
		ft_print_percent(list);
	if (*s)
		s++;
	return (s);
}
