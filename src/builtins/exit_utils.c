/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:50:50 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 15:50:10 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	would_overflow(unsigned long long value,
		unsigned long long limit, char digit)
{
	if (value > limit / 10)
		return (1);
	if (value == limit / 10
		&& (unsigned long long)(digit - '0') > limit % 10)
		return (1);
	return (0);
}

static unsigned long long	get_exit_limit(char *arg, int *i, int *sign)
{
	*sign = 1;
	*i = 0;
	if (arg[*i] == '+' || arg[*i] == '-')
	{
		if (arg[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (*sign < 0)
		return (LLONG_MAX + 1ULL);
	return (LLONG_MAX);
}

int	parse_exit_value(char *arg, unsigned char *status)
{
	int					i;
	int					sign;
	unsigned long long	value;
	unsigned long long	limit;

	value = 0;
	limit = get_exit_limit(arg, &i, &sign);
	if (!arg[i])
		return (0);
	while (ft_isdigit(arg[i]))
	{
		if (would_overflow(value, limit, arg[i]))
			return (0);
		value = value * 10 + (arg[i] - '0');
		i++;
	}
	if (arg[i])
		return (0);
	if (sign < 0)
		*status = (unsigned char)((256 - (value % 256)) % 256);
	else
		*status = (unsigned char)(value % 256);
	return (1);
}

void	print_exit_numeric_error(t_shell *shell, char *arg)
{
	print_shell_prefix(shell);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

void	cleanup_shell_exit(t_shell *shell)
{
	if (shell->current_line)
		free(shell->current_line);
	if (shell->parser)
		free_parser_data(shell->parser);
	else if (shell->ast)
		free_ast(shell->ast);
	free_env_list(&shell->env);
	rl_clear_history();
}
