/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:29:13 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/04 20:59:16 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (size && dst)
	{
		if (ft_strlen(src) < size - 1)
		{
			ft_memcpy(dst, src, ft_strlen(src));
			dst[ft_strlen(src)] = '\0';
		}
		else
		{
			ft_memcpy(dst, src, size - 1);
			dst[size - 1] = '\0';
		}
	}
	return (ft_strlen(src));
}
