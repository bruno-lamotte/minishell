/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:00:41 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/04 21:37:00 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = 0;
	while (dstlen < size && dst[dstlen])
		dstlen++;
	if (size == dstlen)
		return (srclen + size);
	if (size - 1 - dstlen > 0)
	{
		if (srclen < size - 1 - dstlen)
			ft_memcpy(dst + dstlen, src, srclen);
		else
			ft_memcpy(dst + dstlen, src, size - 1 - dstlen);
	}
	if (srclen < size - 1 - dstlen)
		dst[dstlen + srclen] = '\0';
	else
		dst[size - 1] = '\0';
	return (srclen + dstlen);
}
