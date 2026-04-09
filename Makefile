NAME            = minishell
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g3 -MMD -MP

SRC_DIR         = src
OBJ_DIR         = obj
INC_DIR         = inc
LIBFT_DIR       = libft

SHELL_SRC_FILES = parsing/lexer.c \
                  parsing/parser.c \
                  parsing/tokenizer_utils.c \
                  parsing/tokenizer_quote.c \
                  parsing/tokenizer.c \
                  parsing/initialize_table_rows.c \
                  parsing/initialize_rules.c \
                  parsing/initialize_symbols.c \
                  parsing/reduce/pop_redirect.c \
                  parsing/reduce/reduce_cmd.c \
                  parsing/reduce/reduce_cmd_pop.c \
                  parsing/reduce/reduce_clear.c \
                  parsing/reduce/reduce_others.c \
                  parsing/reduce/reduce_ast_nodes.c \
                  parsing/reduce/reduce_symbol.c \
                  parsing/reduce/reduce_utils.c \
                  shell/main.c \
                  shell/parser_init.c \
                  shell/parser_exec.c \
                  shell/parser_syntax.c \
                  shell/parser_state.c \
                  shell/heredoc.c \
                  shell/heredoc_utils.c \
                  shell/env_core.c \
                  shell/env_array.c \
                  shell/env_extra.c \
                  shell/free_common.c \
                  shell/free_parser.c \
                  shell/print_utils.c \
                  shell/read_line.c \
                  shell/read_line_utils.c \
                  shell/line_normalize.c \
                  shell/line_normalize_utils.c \
                  shell/shell_init.c \
                  shell/terminal.c \
                  signals.c \
                  builtins/pwd.c \
                  builtins/echo.c \
                  builtins/cd.c \
                  builtins/cd_home.c \
                  builtins/cd_utils.c \
                  builtins/env.c \
                  builtins/export/export.c \
                  builtins/export/export_line.c \
                  builtins/export/export_parse.c \
                  builtins/export/export_utils.c \
                  builtins/unset.c \
                  builtins/exit.c \
                  builtins/exit_utils.c \
                  exec/exec_common.c \
                  exec/expand.c \
                  exec/expand_buffer.c \
                  exec/expand_parse_quotes.c \
                  exec/expand_encode.c \
                  exec/expand_fields.c \
                  exec/expand_split.c \
                  exec/expand_word.c \
                  exec/expand_ast.c \
                  exec/expand_ast_utils.c \
                  exec/redirections.c \
                  exec/redirections_open.c \
                  exec/exec_cmd.c \
                  exec/exec_child.c \
                  exec/exec_child_utils.c \
                  exec/exec_pipe.c \
                  exec/exec_pipe_stage.c \
                  exec/exec_wait.c \
                  exec/path_utils.c \
                  exec/wildcard.c \
                  exec/wildcard_utils.c \
                  exec/path_search.c \
                  exec/exec.c

SHELL_SRCS      = $(addprefix $(SRC_DIR)/, $(SHELL_SRC_FILES))
SHELL_OBJS      = $(SHELL_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SHELL_DEPS      = $(SHELL_OBJS:.o=.d)

LIBFT           = $(LIBFT_DIR)/libft.a
INCLUDES        = -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS_FLAGS      = $(LIBFT)

all: $(NAME)

$(NAME): $(LIBFT) $(SHELL_OBJS)
	$(CC) $(CFLAGS) $(SHELL_OBJS) $(LIBS_FLAGS) -lreadline -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Compiling Libft..."
	@make -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "Executables removed."

re: fclean all

-include $(SHELL_DEPS)

.PHONY: all clean fclean re
