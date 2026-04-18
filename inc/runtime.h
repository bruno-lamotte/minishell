/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:27:31 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/09 13:33:21 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

void		setup_signals(void);
void		setup_heredoc_signals(void);
void		setup_wait_signals(void);
void		save_shell_terminal(t_shell *shell);
void		restore_shell_terminal(t_shell *shell);
void		cleanup_shell_terminal(t_shell *shell);
void		prepare_foreground_job(t_shell *shell);
void		finish_foreground_job(t_shell *shell);
int			wait_for_pid(pid_t pid, int *status);
int			wait_foreground_job(t_shell *shell, pid_t pid);

int			builtin_pwd(void);
int			builtin_echo(char **args);
int			builtin_cd(t_shell *shell, char **args);
int			builtin_env(t_shell *shell);
int			builtin_export(t_shell *shell, char **args);
void		print_export(t_list *env);
int			builtin_unset(t_shell *shell, char **args);
int			builtin_exit(t_shell *shell, char **args);
int			parse_exit_value(char *arg, unsigned char *status);
void		print_exit_numeric_error(t_shell *shell, char *arg);
void		cleanup_shell_exit(t_shell *shell);
t_list		*find_var(t_list *env, char *arg);
int			env_export_arg(t_list **env, char *arg);
int			env_assign_arg(t_list **env, char *arg);
int			env_unset_arg(t_list **env, char *arg);
int			env_has_value(char *entry);
t_list		*env_dup_list(t_list *env);
void		free_env_list(t_list **env);
void		free_string(void *content);
void		print_shell_prefix(t_shell *shell);
void		print_command_name(char *cmd);
void		clear_list_nodes(t_list **list);
void		free_token(void *content);
void		free_redirection(void *content);
void		free_stack_node(void *content);
void		free_parser_data(t_parser *data);
void		free_ast(t_ast *node);

char		*read_stdin_line(t_shell *shell);
char		*read_plain_line(void);
int			grow_line_buffer(char **buf, size_t *cap, size_t len);
int			line_has_open_quote(char *line);
int			line_has_continuation(char *line);
char		*join_input_lines(char *line, char *next, int continued);
void		init_shell(t_shell *shell, char **envp);
char		*normalize_input_line(char *line);
char		*get_env_val(t_shell *shell, char *name, int len);

char		*expand_string(char *str, t_shell *shell);
char		*expand_heredoc_line(char *line, t_shell *shell);
char		*dequote_string(char *str);
char		**expand_word(char *str, t_shell *shell, int *count);
void		expand_ast(t_ast *node, t_shell *shell);
char		**get_wildcard_matches(char *pattern, int *count);

int			apply_redirections(t_list *redirs, t_shell *shell);
char		**env_to_arr(t_shell *shell);
char		*find_path(char *cmd, t_shell *shell, int *status);
void		exec_in_child(t_ast *node, t_shell *shell);
void		exit_child_process(t_shell *shell, t_list **extra_env, int status);
int			exec_command(t_ast *node, t_shell *shell);
int			wait_status_code(int status);
int			run_builtin(t_shell *shell, char **args);
int			is_builtin_command(char **args);
int			is_env_fallback_builtin(t_shell *shell, char **args);
void		apply_assignments(t_shell *shell, t_ast *node);
void		print_command_error(t_shell *shell, char *cmd, int status);
void		reorder_env_output(char **envp);
int			is_env_program(char *path);
int			exec_pipe(t_ast *node, t_shell *shell);
int			execute(t_ast *node, t_shell *shell);

#endif
