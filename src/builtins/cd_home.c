/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <pwd.h>

char	*get_cd_home(t_shell *shell)
{
	struct passwd	*passwd;
	char			*home;

	home = get_env_val(shell, "HOME", 4);
	if (home)
		return (home);
	passwd = getpwuid(getuid());
	if (!passwd || !passwd->pw_dir)
		return (NULL);
	return (passwd->pw_dir);
}
