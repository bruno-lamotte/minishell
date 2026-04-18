/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:08:56 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/15 21:18:00 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		update_path_var(t_shell *shell, char *name, char *value);
int		print_cd_error(t_shell *shell, char *path);
char	*resolve_cd_path(t_shell *shell, char *arg, int *allocated);
int		update_pwd(t_shell *shell, char *oldpwd);
void	free_path_if_needed(char *path, int allocated);

static int	handle_cd_env_error(t_shell *shell, char *arg)
{
	print_shell_prefix(shell);
	if (arg && !ft_strcmp(arg, "-"))
		ft_putendl_fd("cd: OLDPWD not set", 2);
	else
		ft_putendl_fd("cd: HOME not set", 2);
	return (1);
}

static int	change_to_path(t_shell *shell, char *path, int allocated)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) < 0)
		return (free(oldpwd), free_path_if_needed(path, allocated),
			print_cd_error(shell, path));
	if (!update_pwd(shell, oldpwd))
		return (free(oldpwd), free_path_if_needed(path, allocated), 1);
	free(oldpwd);
	free_path_if_needed(path, allocated);
	return (0);
}

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path;
	int		allocated;

	if (args[2])
	{
		print_shell_prefix(shell);
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	}
	if (args[1] && !args[1][0])
		return (0);
	path = resolve_cd_path(shell, args[1], &allocated);
	if (!path)
		return (handle_cd_env_error(shell, args[1]));
	if (args[1] && !ft_strcmp(args[1], "-"))
		ft_putendl_fd(path, 1);
	return (change_to_path(shell, path, allocated));
}
