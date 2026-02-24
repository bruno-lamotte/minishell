/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:39:12 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 05:23:10 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_int(t_data *list)
{
	long long	n;
	char		*prefix;

	n = va_arg(list->args, int);
	prefix = "";
	if (n < 0)
	{
		n = -n;
		prefix = "-";
	}
	else if (list->plus)
		prefix = "+";
	else if (list->space)
		prefix = " ";
	ft_print_nb_base((unsigned long long)n, "0123456789", prefix, list);
}

void	ft_print_unsigned(t_data *list)
{
	unsigned int	n;

	n = va_arg(list->args, unsigned int);
	ft_print_nb_base((unsigned long long)n, "0123456789", "", list);
}

void	ft_print_hex(t_data *list, char type)
{
	unsigned int	n;
	char			*base;
	char			*prefix;

	n = va_arg(list->args, unsigned int);
	prefix = "";
	if (type == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (list->hash && n != 0)
	{
		if (type == 'x')
			prefix = "0x";
		else
			prefix = "0X";
	}
	ft_print_nb_base((unsigned long long)n, base, prefix, list);
}

void	ft_print_ptr(t_data *list)
{
	unsigned long long	ptr;
	char				*s;
	int					len;

	ptr = va_arg(list->args, unsigned long long);
	if (!ptr)
	{
		s = "(nil)";
		len = 5;
		if (list->width > len && !list->dash)
			ft_print_spaces(len, list);
		ft_putstr_buffer(s, list);
		if (list->width > len && list->dash)
			ft_print_spaces(len, list);
		return ;
	}
	ft_print_nb_base(ptr, "0123456789abcdef", "0x", list);
}
