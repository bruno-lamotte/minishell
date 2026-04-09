/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:27:39 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 11:21:57 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string(void *content)
{
	free(content);
}

void	clear_list_nodes(t_list **list)
{
	t_list	*next;

	while (*list)
	{
		next = (*list)->next;
		free(*list);
		*list = next;
	}
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	free(token->value);
	free(token);
}

void	free_redirection(void *content)
{
	t_redirection	*redir;

	redir = (t_redirection *)content;
	if (!redir)
		return ;
	free(redir->file);
	free(redir->delimiter);
	free(redir);
}
