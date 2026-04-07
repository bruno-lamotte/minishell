/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_name_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg[0] || arg[0] == '=' || ft_isdigit(arg[0]))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!is_name_char(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_name_len(char *arg, int *append)
{
	int	i;

	*append = 0;
	if (!arg[0] || arg[0] == '=' || ft_isdigit(arg[0]))
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			*append = 1;
			return (i);
		}
		if (!is_name_char(arg[i]))
			return (0);
		i++;
	}
	return (i);
}

static char	*build_append_entry(char *name, char *current, char *suffix)
{
	char	*tmp;
	char	*value;
	char	*entry;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	value = ft_strjoin(current, suffix);
	if (!value)
		return (free(tmp), NULL);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (entry);
}

int	export_append_arg(t_shell *shell, char *arg, int name_len)
{
	char	*name;
	char	*entry;
	char	*current;

	name = ft_substr(arg, 0, name_len);
	if (!name)
		return (0);
	current = get_env_val(shell, name, name_len);
	if (!current)
		current = "";
	entry = build_append_entry(name, current, arg + name_len + 2);
	free(name);
	if (!entry)
		return (0);
	if (!env_assign_arg(&shell->env, entry))
		return (free(entry), 0);
	free(entry);
	return (1);
}
