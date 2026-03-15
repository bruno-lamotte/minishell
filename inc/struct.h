/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:59 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/13 17:47:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <libft.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RET_TO,
	TOKEN_RET_FROM,
	TOKEN_DGREAT,
	TOKEN_DLESS,
	TOKEN_END,
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
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
	NODE_TMP,
	NODE_COMMAND,
	NODE_PIPE,
	NODE_SEQUENCE,
	NODE_AND,
	NODE_OR,
}			t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	int				is_bang;
	int				is_async;
	char			**args;
	t_ast			**children;
	int				nb_children;
}			t_ast;

typedef struct s_stack
{
	int		state_id;
	t_ast	*ast_node;
}			t_stack;

typedef struct s_parser
{
	t_list	*tokens;
	t_list	*rules;
	t_list	*symbols;
	t_list	*states;
}			t_parser;

#endif
