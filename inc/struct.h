/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:59 by blamotte          #+#    #+#             */
/*   Updated: 2026/04/05 20:43:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

typedef struct s_token
{
	char	*type;
	char	*value;
}			t_token;

typedef struct s_reduce_rule
{
	char	*left_symbol;
	int		nb_items;
}			t_reduce_rule;

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
	char	**values;
	int		nb_values;
	t_ast	*ast_node;
}			t_stack;

typedef struct s_slr1
{
	t_list	*rules;
	t_list	*symbols;
	t_list	*states;
}			t_slr1;

typedef struct s_parser
{
	char			**symbols;
	int				**table;
	t_list			*tokens;
	t_list			*stack;
	t_list			*here_docs;
	t_reduce_rule	*rules;

}			t_parser;

typedef struct  s_shell
{
    t_list  *env;
    int exit_code;
}   t_shell;

#endif
