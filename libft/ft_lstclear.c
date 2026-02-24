/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 05:06:43 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/18 05:06:46 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;
	t_list	*previus;

	if (!del || !lst)
		return ;
	l = *lst;
	while (l)
	{
		previus = l;
		l = l->next;
		ft_lstdelone(previus, del);
	}
	*lst = NULL;
}
