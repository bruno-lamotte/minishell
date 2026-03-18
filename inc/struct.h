/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:59 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/18 00:59:41 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <libft.h>

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_rule
{
	int		id;
	char	*left_symbol;
	t_list	*right_symbols;
	int		nb_items;
}			t_rule;

typedef struct s_item
{
	int		id;
	t_rule	*rule_of_item;
	int		dot_pos;
}			t_item;

typedef struct s_symbol
{
	int		nbr;
	char	*name;
	t_list	*firsts;
	t_list	*follows;
}			t_symbol;

typedef struct s_state
{
	int		id;
	t_list	*items;
	t_list	*transitions;
}			t_state;

typedef struct s_transition
{
	char	*symbol;
	t_state	*dest_state;
}			t_transition;

typedef enum e_node_type
{
	UNKNOWN,
	COMMAND,
	SUBSHELL,
	PIPE,
	SEQUENCE,
	AND,
	OR,
}			t_node_type;

typedef enum e_redirection_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}			t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		type;
	char					*file;
}							t_redirection;

typedef struct s_ast
{
	t_node_type		type;
	int				is_bang;
	int				is_async;
	char			**args;
	int				nb_args;
	char			**assignments;
	int				nb_assignments;
	struct s_ast	**children;
	int				nb_children;
	t_list			*redirections;
}					t_ast;

typedef struct s_stack
{
	int		state_id;
	char	*symbol;
	char	**value;
	int		nb_values;
	t_ast	*ast_node;
}			t_stack;

typedef struct s_parser
{
	t_list	*tokens;
	t_list	*rules;
	t_list	*symbols;
	t_list	*states;
	t_list	*stack;
}			t_parser;

#endif
