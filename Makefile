# **************************************************************************** #
#                                 CONFIG                                       #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -MMD -MP

# **************************************************************************** #
#                                 CHEMINS                                      #
# **************************************************************************** #

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = inc
LIBFT_DIR   = libft

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRCS_FILES  = generating_table/closure.c \
				generating_table/get_firsts.c \
				generating_table/get_follows.c \
				generating_table/get_rules.c \
				generating_table/get_symbols.c \
				generating_table/get_table.c \
				generating_table/go_to.c \

SRCS        = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        = $(OBJS:.o=.d)

# **************************************************************************** #
#                                 LIBRARIES                                    #
# **************************************************************************** #

LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS_FLAGS  = $(LIBFT)

# **************************************************************************** #
#                                 RÈGLES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Compiling Libft..."
	@make -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "🧹 Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "🗑️  Executable removed."

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re