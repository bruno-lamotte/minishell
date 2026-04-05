# **************************************************************************** #
#                                 CONFIG                                       #
# **************************************************************************** #
NAME            = minishell
GEN_TABLE       = generating_table
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g3 -MMD -MP

# **************************************************************************** #
#                                 CHEMINS                                      #
# **************************************************************************** #

SRC_DIR         = src
OBJ_DIR         = obj
INC_DIR         = inc
LIBFT_DIR       = libft

# **************************************************************************** #
#                                 GÉNÉRATEUR DE TABLE                          #
# **************************************************************************** #

GEN_SRC_FILES   = generating_table/closure.c \
                  generating_table/get_firsts.c \
                  generating_table/get_follows.c \
                  generating_table/get_rules.c \
                  generating_table/get_symbols.c \
                  generating_table/get_table.c \
                  generating_table/go_to.c \
                  generating_table/print_table.c \
				  generating_table/free_palestine.c

GEN_SRCS        = $(addprefix $(SRC_DIR)/, $(GEN_SRC_FILES))
GEN_OBJS        = $(GEN_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
GEN_DEPS        = $(GEN_OBJS:.o=.d)

# **************************************************************************** #
#                                 MINISHELL                                    #
# **************************************************************************** #

SHELL_SRC_FILES = parsing/lexer.c \
                  parsing/parser.c \
                  parsing/tokenizer_utils.c \
                  parsing/tokenizer.c \
                  parsing/initialize_table.c \
                  parsing/reduce/pop_redirect.c \
                  parsing/reduce/reduce_cmd.c \
                  parsing/reduce/reduce_others.c \
                  parsing/reduce/reduce_utils.c \
                  parsing/main.c \
                  signals.c \
                  builtins/pwd.c \
                  builtins/echo.c \
                  builtins/cd.c \
                  builtins/env.c \
                  builtins/export/export.c \
                  builtins/export/export_utils.c \
                  builtins/unset.c \
                  builtins/exit.c \
                  exec/expand.c \
                  exec/redirections.c \
                  exec/exec_cmd.c \
                  exec/exec_pipe.c \
                  exec/exec.c

SHELL_SRCS      = $(addprefix $(SRC_DIR)/, $(SHELL_SRC_FILES))
SHELL_OBJS      = $(SHELL_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SHELL_DEPS      = $(SHELL_OBJS:.o=.d)

INIT_TABLE_FILE = $(SRC_DIR)/parsing/initialize_table.c

# **************************************************************************** #
#                                 LIBRARIES                                    #
# **************************************************************************** #

LIBFT           = $(LIBFT_DIR)/libft.a
INCLUDES        = -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS_FLAGS      = $(LIBFT)

# **************************************************************************** #
#                                 RÈGLES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(INIT_TABLE_FILE) $(SHELL_OBJS)
	$(CC) $(CFLAGS) $(SHELL_OBJS) $(LIBS_FLAGS) -lreadline -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(INIT_TABLE_FILE): $(GEN_TABLE)
	@echo "Generating parsing table..."
	@./$(GEN_TABLE) > $(INIT_TABLE_FILE)
	@echo "Parsing table generated!"

$(GEN_TABLE): $(LIBFT) $(GEN_OBJS)
	$(CC) $(CFLAGS) $(GEN_OBJS) $(LIBS_FLAGS) -o $(GEN_TABLE)
	@echo "Table generator compiled!"

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
	@rm -f $(NAME) $(GEN_TABLE) $(INIT_TABLE_FILE)
	@make -sC $(LIBFT_DIR) fclean
	@echo "Executables removed."

re: fclean all

-include $(GEN_DEPS) $(SHELL_DEPS)

.PHONY: all clean fclean re