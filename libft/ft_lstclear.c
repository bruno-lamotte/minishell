/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 05:06:43 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/04 09:53:47 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;
	t_list	*previus;

	if (!lst)
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
