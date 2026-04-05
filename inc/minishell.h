/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:51:52 by blamotte          #+#    #+#             */
/*   Updated: 2026/04/05 23:03:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "libft.h"
# include <sys/wait.h>
# include "struct.h"
# include "global_variables.h"

/* ************************************************************************** */
/*                               get_symbols.c                                */
/* ************************************************************************** */

t_list		*get_rule_from_symbolname(t_slr1 *data, char *symbol);
t_symbol	*get_symbol_from_name(t_slr1 *data, char *left_symbol);
int			symbol_is_token(char *name);
void		complete_symbol_name(t_symbol **symbol, char *name);
int			symbol_already_parsed(t_list *symbols, char *left_symbol);
void	    add_symbol_if_not_exists(t_slr1 *data, char *name, int *nbr);
void		get_symbols(t_slr1 *data);

/* ************************************************************************** */
/*                               get_rules.c                                  */
/* ************************************************************************** */

void		get_leftsymbol_from_grammar(t_slr1 *data, t_rule **new_rule,
				char *line);
void		get_id_from_grammar(t_slr1 *data, t_rule **new_rule);
void		get_rightsymbols_from_grammar(t_rule **new_rule,
				char *line);
void		get_nbitems_from_grammar(t_rule **new_rule);
void		get_rule_from_grammar(t_slr1 *data, t_rule **new_rule,
				char *line);
int			parse_grammar(t_slr1 *data);

/* ************************************************************************** */
/*                               get_firsts.c                                 */
/* ************************************************************************** */

int			does_list_contains_this_symbol(t_list *list, char *name);
int			add_firsts_if_not_token(t_slr1 *data, t_rule *next_rule,
				t_symbol *left_symbol);
int			add_first_if_token(t_symbol *left_symbol, t_symbol *right_symbol);
int			should_look_for_next_right_symbol(t_symbol *left_symbol,
				t_rule *rule);
void		get_first_dfs(t_slr1 *data, t_rule *rule, t_symbol *left_symbol,
				t_symbol *right_symbol);
void		get_firsts(t_slr1 *data);

/* ************************************************************************** */
/*                               get_follows.c                                */
/* ************************************************************************** */

void		add_dollar_to_start_symbol(t_slr1 *data);
int			add_follows_from_follows(t_symbol **symbol, t_symbol *next_symbol);
int			add_follows_from_firsts(t_symbol **symbol, t_symbol *next_symbol);
int			contains_empty_in_firsts(t_symbol *symbol);
void		update_follows(t_slr1 *data, t_list *current_rule, int *added);
void		get_follows(t_slr1 *data);

/* ************************************************************************** */
/*                               closure.c                                    */
/* ************************************************************************** */

t_item		*create_new_item(t_rule *rule, int dot_pos);
t_symbol	*get_symbol_from_list(t_slr1 *data, t_list *right_symbols,
				int dot_pos);
t_symbol	*get_symbol_after_dot(t_slr1 *data, t_item *item);
t_symbol	*get_non_terminal_symbol_after_dot(t_slr1 *data, t_item *item);
int			does_state_contains_this_item(t_list *items, t_item *item);
void		closure(t_slr1 *data, t_state *state);

/* ************************************************************************** */
/*                               go_to.c                                      */
/* ************************************************************************** */

t_transition	*create_transition(char *symbol_name, t_state *dest_state);
t_state			*create_new_state(t_slr1 *data);
t_state			*find_state(t_slr1 *data, t_state *new_state);
void			add_item_to_list(t_state **new_state,
					t_item *item);
void			add_transition_to_state(t_slr1 *data, t_state *current_state,
					t_state *new_state, t_symbol *symbol);
void			get_new_state(t_slr1 *data, t_state *current_state,
					t_state *new_state, t_symbol *target_symbol);
void			go_to(t_slr1 *data, t_state *state);

/* ************************************************************************** */
/*                               get_table.c                                  */
/* ************************************************************************** */

int		get_transition_from_symbol(t_state *state, char *symbol_name);
void	fill_table_when_reduce(t_slr1 *data, int ***table, t_list *state,
			t_list *item);
void	fill_parsing_table(t_slr1 *data, int ***table);
t_state	*initialize_first_state(t_slr1 *data);
void	get_states(t_slr1 *data);
void	initialize_data(t_slr1 *data);
int		**create_parsing_table(t_slr1 *data);
void	print_table(int **table, t_slr1 *data);

void	print_table_in_c(int **table, int nb_states, int nb_tokens);
void	print_rules_in_c(t_list *rule_list);
void	print_symbols_in_c(t_list *symbols_list);
void	free_all(t_slr1 *data, int **table);

/* ************************************************************************** */
/*                           initialize_table.c                               */
/* ************************************************************************** */

void	init_table_part_0(int **t);
void	init_table_part_1(int **t);
void	init_table_part_2(int **t);
void	init_table_part_3(int **t);
void	init_table_part_4(int **t);
void	init_rules_part_0(t_reduce_rule *rules);
void	init_rules_part_1(t_reduce_rule *rules);
void	init_rules_part_2(t_reduce_rule *rules);
void	init_rules_part_3(t_reduce_rule *rules);
void	init_symbols_part_0(char **symbols);
void	init_symbols_part_1(char **symbols);

/* ************************************************************************** */
/*                            tokenizer_utils.c                               */
/* ************************************************************************** */

int		is_end_of_imput(char c);
int		is_operator(char c);
int		can_be_added_to_opperator(char c);
int		is_blank(char c);
int		handle_comment(char *str, int *i);
int		is_quote(char c);

/* ************************************************************************** */
/*                               tokenizer.c                                  */
/* ************************************************************************** */

t_token	*make_token(char *str, int i, char *type);
int		handle_is_operator(char *str, int *i);
t_token	*tokenizer_loop(char **str);
t_list	*tokenizer(char *str);

/* ************************************************************************** */
/*                                 lexer.c                                    */
/* ************************************************************************** */

int		is_valid_name(char *str, int len);
t_token	*lex_assignment(t_parser *data, int **table, t_token *token, int state_id);
t_token	*lex_operator(t_token *token);
t_token	*lex_token(t_parser *data, int **table, t_token *token, int state_id);

/* ************************************************************************** */
/*                                 parser.c                                   */
/* ************************************************************************** */

void	shift(t_parser *data, int state_id, t_token *token);
void	reduce(t_parser *data, int **table, int action);
void	print_parsing_error(t_parser *data, int **table, int id, t_token *token);
int		parser(t_parser *data);

/* ************************************************************************** */
/*                            reduce/pop_redirect.c                           */
/* ************************************************************************** */

int		is_redirection_symbol(t_stack *stack);
t_list	*get_redirection_from_symbol(t_parser *data, t_stack *stack);
t_list	*pop_redirections_from_stack(t_parser *data, int lookahead);

/* ************************************************************************** */
/*                              reduce/reduce_cmd.c                           */
/* ************************************************************************** */

int		get_size_of_args(t_parser *data, int lookahead);
int		get_size_of_assignements(t_parser *data, int lookahead);
char	**pop_assignements_from_stack(t_parser *data, int size);
char	**pop_args_from_stack(t_parser *data, int size);
void	reduce_ast_command(t_parser *data, t_reduce_rule *rule,
			t_node_type node_type);

/* ************************************************************************** */
/*                            reduce/reduce_others.c                          */
/* ************************************************************************** */

int		reduce_booleans(t_parser *data, t_reduce_rule *rule);
void	reduce_ast_subshell(t_parser *data, t_reduce_rule *rule,
			t_node_type node_type);
void	reduce_multiple_pipes(t_parser *data, t_reduce_rule *rule);
void	reduce_ast_control(t_parser *data, t_reduce_rule *rule,
			t_node_type node_type);
void	reduce_symbol(t_parser *data, t_reduce_rule *rule);

/* ************************************************************************** */
/*                            reduce/reduce_utils.c                           */
/* ************************************************************************** */

t_node_type	get_node_type_from_rule(t_reduce_rule *rule, t_list *stack);
int			is_node_already_type(t_parser *data, int lookahead,
				t_node_type node_type);
int			get_symbol_nbr(t_parser *data, char *symbol);
int			get_next_state_after_reduce(t_parser *data, int **table,
				t_reduce_rule *rule);
void		free_char_array(char **array, int size);
void		clear_stack_after_reduce(t_parser *data, int nb_items,
				int should_free_ast);

void		set_row(int **table, int state_index, char *values);

/* ************************************************************************** */
/*                               signals.c                                    */
/* ************************************************************************** */

void	setup_signals(void);

/* ************************************************************************** */
/*                               builtins                                     */
/* ************************************************************************** */

int		builtin_pwd(void);
int		builtin_echo(char **args);
int		builtin_cd(t_shell *shell, char **args);
int		builtin_env(t_shell *shell);
int		builtin_export(t_shell *shell, char **args);
int		builtin_unset(t_shell *shell, char **args);
int		builtin_exit(t_shell *shell, char **args);
t_list	*find_var(t_list *env, char *arg);

/* ************************************************************************** */
/*                               heredoc.c                                    */
/* ************************************************************************** */

char	*generate_tmp_filename(void);
int		read_heredoc(t_redirection *redir);
int		open_heredocs(t_parser *data);

/* ************************************************************************** */
/*                                expand                                      */
/* ************************************************************************** */

char	*expand_string(char *str, t_shell *shell);
void	expand_ast(t_ast *node, t_shell *shell);

void	expand_wildcards_args(t_ast *node);
char	**get_wildcard_matches(char *pattern, int *count);

#endif