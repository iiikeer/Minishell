CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lncurses -lreadline

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj

SRC =  $(wildcard $(SRC_DIR)/execution/*.c)				\
	   $(wildcard $(SRC_DIR)/execution/builtins/*.c)	\
	   $(wildcard $(SRC_DIR)/initialization/*.c)		\
	   $(wildcard $(SRC_DIR)/libft/*.c)					\
	   $(wildcard $(SRC_DIR)/nodes/*.c)					\
	   $(wildcard $(SRC_DIR)/utils/*.c) 				\
	   $(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "\033[32mMinishell has been successfully compiled\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/execution/builtins
	@mkdir -p $(OBJ_DIR)/initialization
	@mkdir -p $(OBJ_DIR)/libft
	@mkdir -p $(OBJ_DIR)/nodes
	@mkdir -p $(OBJ_DIR)/utils

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mObjects cleaned\033[0m"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo "\033[31mObjects and executable cleaned\033[0m"
	
re: fclean all

usage:
	@echo "\033[33m./minishell\033[0m"

.PHONY: all clean fclean re usage