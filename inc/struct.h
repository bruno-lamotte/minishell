#ifndef STRUCT_H
# define STRUCT_H

# include <minishell.h>

typedef struct s_token
{
	int				type;
	char			*value;
}					t_token;

typedef struct s_rule
{
	int				id;
	char			*left_symbol;
	t_list			*right_symbols;
	int				nb_items;
}					t_rule;

typedef struct s_item
{
	int				id;
	t_rule			*rule_of_item;
	int				dot_pos;
}					t_item;

typedef struct s_symbol
{
	char			*name;
	t_list			*firsts;
	t_list			*follows;
}					t_symbol;

typedef struct s_state
{
	int				id;
	t_list			*items;
	t_list			*transitions;
	int				reduction_rule_id;
}					t_state;

typedef struct s_transition
{
	char			*symbol;
	struct s_state	*dest_state;
}					t_transition;

typedef struct s_stack
{
	int				state_id;
	t_ast			*ast_node;
}					t_stack;

typedef struct s_ast
{
	char			*type;
	char			*value;
	t_list			*children;
}					t_ast;

typedef struct s_parser
{
	t_list			*tokens;
	t_list			*rules;
	t_list			*symbols;
	t_list			*states;
}					t_parser;

#endif