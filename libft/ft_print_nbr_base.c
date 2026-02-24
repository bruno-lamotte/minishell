/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:36:37 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 02:52:48 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen_base(unsigned long long n, int base_len)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

void	ft_putnbr_recursive(unsigned long long n, char *base, t_data *list)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (n >= base_len)
		ft_putnbr_recursive(n / base_len, base, list);
	ft_putchar_buffer(base[n % base_len], list);
}

void	ft_put_n_char(int len, char c, t_data *list)
{
	while (len-- > 0)
		ft_putchar_buffer(c, list);
}

void	ft_print_nbr_base_nodash(char *prefix, int len_spaces, t_data *list)
{
	if (list->zero)
	{
		ft_putstr_buffer(prefix, list);
		ft_put_n_char(len_spaces, '0', list);
	}
	else
	{
		ft_put_n_char(len_spaces, ' ', list);
		ft_putstr_buffer(prefix, list);
	}
}

void	ft_print_nb_base(unsigned long long n, char *base, char *prefix,
		t_data *list)
{
	int	len_nb;
	int	len_zeros;
	int	len_spaces;

	if (n == 0 && list->point && list->precision == 0)
		len_nb = 0;
	else
		len_nb = ft_nbrlen_base(n, ft_strlen(base));
	len_zeros = 0;
	if (list->point && list->precision > len_nb)
		len_zeros = list->precision - len_nb;
	if (list->point)
		list->zero = 0;
	len_spaces = 0;
	if (list->width > ((int)ft_strlen(prefix) + len_zeros + len_nb))
		len_spaces = list->width - (ft_strlen(prefix) + len_zeros + len_nb);
	if (!list->dash)
		ft_print_nbr_base_nodash(prefix, len_spaces, list);
	else
		ft_putstr_buffer(prefix, list);
	ft_put_n_char(len_zeros, '0', list);
	if (len_nb > 0)
		ft_putnbr_recursive(n, base, list);
	if (list->dash)
		ft_put_n_char(len_spaces, ' ', list);
}
