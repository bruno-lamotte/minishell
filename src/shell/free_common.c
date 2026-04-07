/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
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
