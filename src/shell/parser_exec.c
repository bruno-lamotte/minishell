/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:26:02 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/11 00:10:37 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MASK_SQUOTE '\3'
#define MASK_DQUOTE '\4'
#define MASK_NEWLINE '\5'
#define MASK_BANG '\7'

int	has_balanced_parentheses(char *line);

static void	normalize_token_types(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token && token->type)
		{
			if (!ft_strcmp(token->type, "WORD"))
			{
				free(token->type);
				token->type = "WORD";
			}
			else if (!ft_strcmp(token->type, "OPERATOR"))
			{
				free(token->type);
				token->type = "OPERATOR";
			}
			else if (!ft_strcmp(token->type, "$"))
			{
				free(token->type);
				token->type = "$";
			}
		}
		tokens = tokens->next;
	}
}

static void	restore_token_values(t_list *tokens)
{
	t_token	*token;
	int		i;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		i = 0;
		while (token && token->value && token->value[i])
		{
			if (token->value[i] == MASK_SQUOTE)
				token->value[i] = '\'';
			else if (token->value[i] == MASK_DQUOTE)
				token->value[i] = '"';
			else if (token->value[i] == MASK_NEWLINE)
				token->value[i] = '\n';
			else if (token->value[i] == MASK_BANG)
				token->value[i] = '!';
			i++;
		}
		tokens = tokens->next;
	}
}

static int	handle_parse_error(t_shell *shell)
{
	ft_putendl_fd("minishell: parse error", 2);
	shell->exit_code = 2;
	if (!shell->interactive)
		shell->should_exit = 1;
	return (2);
}

static int	execute_parsed_ast(t_parser *data, t_shell *shell)
{
	t_ast	*ast;

	if (!open_heredocs(data, shell))
		return (shell->exit_code);
	ast = ((t_stack *)data->stack->content)->ast_node;
	shell->parser = data;
	shell->ast = ast;
	if (ast)
		shell->exit_code = execute(ast, shell);
	shell->ast = NULL;
	shell->parser = NULL;
	return (shell->exit_code);
}

int	exec_line(t_parser *data, t_shell *shell, char *line)
{
	char	*normalized;

	normalized = normalize_input_line(line);
	if (!normalized)
		return (1);
	if (!has_balanced_parentheses(normalized))
		return (free(normalized), handle_parse_error(shell));
	data->tokens = tokenizer(normalized);
	free(normalized);
	restore_token_values(data->tokens);
	normalize_token_types(data->tokens);
	if (!data->tokens || !parser(data))
		return (handle_parse_error(shell));
	return (execute_parsed_ast(data, shell));
}
