/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:58:26 by blamotte          #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\0');
}

void	set_row(int **table, int state_index, char *values)
{
	char	**split;
	int		i;

	split = ft_split(values, ' ');
	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		table[state_index][i] = ft_atoi(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}

static t_parser	init_parser_data(void)
{
	t_parser	data;
	int			i;

	ft_bzero(&data, sizeof(t_parser));
	data.table = malloc(sizeof(int *) * 57);
	i = 0;
	while (i < 57)
	{
		data.table[i] = ft_calloc(34, sizeof(int));
		i++;
	}
	data.rules = malloc(sizeof(t_reduce_rule) * 43);
	data.symbols = malloc(sizeof(char *) * 35);
	ft_bzero(data.symbols, sizeof(char *) * 35);
	init_table_part_0(data.table);
	init_rules_part_0(data.rules);
	init_symbols_part_0(data.symbols);
	return (data);
}

static void	reset_parser(t_parser *p)
{
	ft_lstclear(&p->tokens, NULL);
	ft_lstclear(&p->stack, NULL);
	ft_lstclear(&p->here_docs, NULL);
	p->tokens = NULL;
	p->stack = NULL;
	p->here_docs = NULL;
	ft_lstadd_front(&p->stack, ft_lstnew(ft_calloc(sizeof(t_stack), 1)));
}

static void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->env = NULL;
	shell->exit_code = 0;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&shell->env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	t_parser	data;
	char		*line;
	t_ast		*ast;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	setup_signals();
	data = init_parser_data();
	while (1)
	{
		reset_parser(&data);
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (is_blank_line(line))
		{
			free(line);
			continue ;
		}
		data.tokens = tokenizer(line);
		free(line);
		if (!parser(&data))
		{
			ft_printf("minishell: parse error\n");
			continue ;
		}
		ast = ((t_stack *)(data.stack->content))->ast_node;
		if (ast)
			shell.exit_code = execute(ast, &shell);
		if (g_signal == SIGINT)
			g_signal = 0;
	}
	ft_printf("exit\n");
	return (shell.exit_code);
}
