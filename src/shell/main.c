/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\0' || line[i] == '#');
}

static char	*read_shell_line(t_shell *shell)
{
	if (shell->interactive)
	{
		restore_shell_terminal(shell);
		return (readline("minishell> "));
	}
	return (read_stdin_line(shell));
}

static void	handle_sigint_line(t_shell *shell)
{
	if (g_signal != SIGINT)
		return ;
	shell->exit_code = 130;
	g_signal = 0;
}

static int	run_shell_loop(t_shell *shell, t_parser *parser)
{
	char	*line;

	while (!shell->should_exit)
	{
		reset_parser(parser);
		line = read_shell_line(shell);
		if (!line)
			return (1);
		shell->current_line = line;
		handle_sigint_line(shell);
		if (shell->interactive && *line)
			add_history(line);
		if (is_blank_line(line))
		{
			free(line);
			shell->current_line = NULL;
			continue ;
		}
		shell->exit_code = exec_line(parser, shell, line);
		free(line);
		shell->current_line = NULL;
		g_signal = 0;
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	t_parser	parser;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	setup_signals();
	parser = init_parser_data();
	run_shell_loop(&shell, &parser);
	if (shell.interactive && !shell.should_exit)
		ft_putendl_fd("exit", STDERR_FILENO);
	free_parser_data(&parser);
	free_env_list(&shell.env);
	cleanup_shell_terminal(&shell);
	return (shell.exit_code);
}
