/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:42:54 by marvin            #+#    #+#             */
/*   Updated: 2026/04/11 07:29:26 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if ((unsigned char)*s1 - (unsigned char)*s2 < 0)
		return (-1);
	else if ((unsigned char)*s1 - (unsigned char)*s2 > 0)
		return (1);
	else
		return (0);
}
