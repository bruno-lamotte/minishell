/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_home(t_shell *shell);

int	update_path_var(t_shell *shell, char *name, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (0);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return (0);
	if (!env_assign_arg(&shell->env, entry))
		return (free(entry), 0);
	free(entry);
	return (1);
}

int	print_cd_error(t_shell *shell, char *path)
{
	print_shell_prefix(shell);
	ft_putstr_fd("cd: ", 2);
	perror(path);
	return (1);
}

char	*resolve_cd_path(t_shell *shell, char *arg, int *allocated)
{
	char	*home;
	char	*path;

	*allocated = 0;
	if (!arg || !ft_strcmp(arg, "--"))
		return (get_env_val(shell, "HOME", 4));
	if (!ft_strcmp(arg, "~"))
		return (*allocated = 1, get_cd_home(shell));
	if (!ft_strcmp(arg, "-"))
		return (get_env_val(shell, "OLDPWD", 6));
	if (ft_strncmp(arg, "~/", 2))
		return (arg);
	home = get_cd_home(shell);
	if (!home)
		return (NULL);
	path = ft_strjoin(home, arg + 1);
	free(home);
	*allocated = 1;
	return (path);
}

int	update_pwd(t_shell *shell, char *oldpwd)
{
	char	*cwd;

	if (oldpwd && !update_path_var(shell, "OLDPWD", oldpwd))
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	if (!update_path_var(shell, "PWD", cwd))
		return (free(cwd), 0);
	free(cwd);
	return (1);
}

void	free_path_if_needed(char *path, int allocated)
{
	if (allocated)
		free(path);
}
