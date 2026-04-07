/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *arg);
int	get_name_len(char *arg, int *append);
int	export_append_arg(t_shell *shell, char *arg, int name_len);

static void	print_export_usage(void)
{
	ft_putendl_fd("export: usage: export [-fn] [name[=value] ...] or export -p",
		2);
}

static void	print_export_option(t_shell *shell, char *arg)
{
	print_shell_prefix(shell);
	ft_putstr_fd("export: ", 2);
	if (arg[1] == '-')
		ft_putstr_fd("--", 2);
	else
	{
		ft_putchar_fd('-', 2);
		ft_putchar_fd(arg[1], 2);
	}
	ft_putendl_fd(": invalid option", 2);
	print_export_usage();
}

static int	export_option_error(t_shell *shell, char *arg)
{
	if (arg[0] == '-' && arg[1])
	{
		print_export_option(shell, arg);
		return (1);
	}
	return (0);
}

static void	export_identifier_error(t_shell *shell, char *arg)
{
	print_shell_prefix(shell);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	int	ret;
	int	append;
	int	name_len;

	if (!args[1])
		return (print_export(shell->env), 0);
	i = 1;
	ret = 0;
	while (args[i])
	{
		name_len = get_name_len(args[i], &append);
		if (export_option_error(shell, args[i]))
			ret = 2;
		else if (!name_len || (!append && !is_valid_identifier(args[i])))
			ret = (export_identifier_error(shell, args[i]), 1);
		else if (append && !export_append_arg(shell, args[i], name_len))
			return (1);
		else if (!env_export_arg(&shell->env, args[i]))
			return (1);
		i++;
	}
	return (ret);
}
