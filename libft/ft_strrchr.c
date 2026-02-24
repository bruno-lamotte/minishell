/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:54:33 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/05 16:12:58 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	slen;

	slen = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)s + slen);
	while (slen--)
		if ((unsigned char)s[slen] == (unsigned char)c)
			return ((char *)s + slen);
	return (NULL);
}
