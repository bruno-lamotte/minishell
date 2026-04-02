/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 02:38:13 by user              #+#    #+#             */
/*   Updated: 2026/04/02 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(t_shell *shell, char *name)
{
	t_list	*current;
	char	*content;
	int		len;

	len = ft_strlen(name);
	current = shell->env;
	while (current)
	{
		content = current->content;
		if (ft_strncmp(content, name, len) == 0 && content[len] == '=')
			return (content + len + 1);
		current = current->next;
	}
	return (NULL);
}

static void	set_env_value(t_shell *shell, char *name, char *value)
{
	t_list	*current;
	char	*content;
	int		len;
	char	*new_content;

	len = ft_strlen(name);
	current = shell->env;
	while (current)
	{
		content = current->content;
		if (ft_strncmp(content, name, len) == 0 && content[len] == '=')
		{
			new_content = ft_strjoin(ft_strjoin(name, "="), value);
			free(current->content);
			current->content = new_content;
			return ;
		}
		current = current->next;
	}
	new_content = ft_strjoin(ft_strjoin(name, "="), value);
	ft_lstadd_back(&shell->env, ft_lstnew(new_content));
}

static int	cd_error(char *path)
{
	struct stat	st;

	ft_printf("minishell: cd: %s", path);
	if (stat(path, &st) == -1)
		ft_printf(": No such file or directory\n");
	else if (!(st.st_mode & S_IXUSR))
		ft_printf(": Permission denied\n");
	else
		ft_printf(": Not a directory\n");
	return (1);
}

static char	*resolve_path(t_shell *shell, char *arg)
{
	char	*home;
	char	*rest;

	if (!arg || ft_strncmp(arg, "~", 2) == 0
		|| ft_strncmp(arg, "--", 3) == 0)
		return (get_env_value(shell, "HOME"));
	if (ft_strncmp(arg, "~/", 2) == 0)
	{
		home = get_env_value(shell, "HOME");
		if (!home)
			return (NULL);
		rest = arg + 1;
		return (ft_strjoin(home, rest));
	}
	return (arg);
}

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path;
	char	*oldpwd;

	if (args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_value(shell, "OLDPWD");
		if (!path)
			return (write(2, "minishell: cd: OLDPWD not set\n", 30), 1);
		ft_printf("%s\n", path);
	}
	else
		path = resolve_path(shell, args[1]);
	if (!path)
		return (write(2, "minishell: cd: HOME not set\n", 28), 1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(oldpwd);
		return (cd_error(path));
	}
	if (oldpwd)
		set_env_value(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	oldpwd = getcwd(NULL, 0);
	if (oldpwd)
	{
		set_env_value(shell, "PWD", oldpwd);
		free(oldpwd);
	}
	return (0);
}
