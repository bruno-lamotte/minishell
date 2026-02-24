/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:02:33 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/10 17:59:25 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	char	*out;
	long	nb;
	int		len;

	nb = n;
	len = (n <= 0);
	while (n && ++len)
		n /= 10;
	out = ft_calloc(len + 1, sizeof(char));
	if (!out)
		return (NULL);
	if (nb < 0)
	{
		out[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		out[0] = '0';
	while (nb)
	{
		out[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (out);
}
