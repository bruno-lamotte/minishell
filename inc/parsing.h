/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:03:22 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 19:22:14 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int			is_end_of_imput(char c);
int			is_operator(char c);
int			can_be_added_to_opperator(char c);
int			is_blank(char c);
int			handle_comment(char *str, int *i);
int			is_quote(char c);

t_token		*make_token(char *str, int i, char *type);
int			handle_is_operator(char *str, int *i);
t_token		*tokenizer_loop(char **str);
t_list		*tokenizer(char *str);

int			is_valid_name(char *str, int len);
t_token		*lex_assignment(t_parser *data, int **table, t_token *token,
				int state_id);
t_token		*lex_operator(t_token *token);
t_token		*lex_token(t_parser *data, int **table, t_token *token,
				int state_id);

void		shift(t_parser *data, int state_id, t_token *token);
void		reduce(t_parser *data, int **table, int action);
void		print_parsing_error(t_parser *data, int **table, int id,
				t_token *token);
int			parser(t_parser *data);

int			is_redirection_symbol(t_stack *stack);
t_list		*get_redirection_from_symbol(t_parser *data, t_stack *stack);
t_list		*pop_redirections_from_stack(t_parser *data, int lookahead);

int			get_size_of_args(t_parser *data, int lookahead);
int			get_size_of_assignements(t_parser *data, int lookahead);
char		**pop_assignements_from_stack(t_parser *data, int size);
char		**pop_args_from_stack(t_parser *data, int size);
void		reduce_ast_command(t_parser *data, t_reduce_rule *rule,
				t_node_type node_type);

int			reduce_booleans(t_parser *data, t_reduce_rule *rule);
void		reduce_ast_subshell(t_parser *data, t_reduce_rule *rule,
				t_node_type node_type);
void		reduce_multiple_pipes(t_parser *data, t_reduce_rule *rule);
void		reduce_ast_control(t_parser *data, t_reduce_rule *rule,
				t_node_type node_type);
void		reduce_symbol(t_parser *data, t_reduce_rule *rule);

t_node_type	get_node_type_from_rule(t_reduce_rule *rule, t_list *stack);
int			is_node_already_type(t_parser *data, int lookahead,
				t_node_type node_type);
int			get_symbol_nbr(t_parser *data, char *symbol);
int			get_next_state_after_reduce(t_parser *data, int **table,
				t_reduce_rule *rule);
void		free_char_array(char **array, int size);
void		clear_stack_after_reduce(t_parser *data, int nb_items,
				int should_free_ast);

char		*generate_tmp_filename(void);
int			heredoc_has_quotes(char *str);
char		*read_heredoc_line(t_shell *shell);
int			write_heredoc_line(int fd, char *line, t_redirection *redir,
				t_shell *shell);
int			read_heredoc(t_redirection *redir, t_shell *shell);
int			open_heredocs(t_parser *data, t_shell *shell);
int			exec_line(t_parser *data, t_shell *shell, char *line);
t_parser	init_parser_data(void);
void		reset_parser(t_parser *parser);

#endif
