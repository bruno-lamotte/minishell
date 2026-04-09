/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:12:24 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/06 13:36:12 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection(t_redirection *redir, t_shell *shell);

static int	print_ambiguous_error(t_shell *shell, char *file)
{
	print_shell_prefix(shell);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (0);
}

static int	apply_redirections_in_order(t_list *redirs, t_shell *shell)
{
	t_redirection	*redir;

	if (!redirs)
		return (1);
	if (!apply_redirections_in_order(redirs->next, shell))
		return (0);
	redir = (t_redirection *)redirs->content;
	if (redir->ambiguous)
		return (print_ambiguous_error(shell, redir->file));
	if (!open_redirection(redir, shell))
		return (0);
	return (1);
}

int	apply_redirections(t_list *redirs, t_shell *shell)
{
	return (apply_redirections_in_order(redirs, shell));
}
