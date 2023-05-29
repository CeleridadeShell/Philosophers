NAME			= philosophers

HEADER_DIR		= ./include/
HEADER			= philosophers.h
HEADER_PATH		= $(addprefix $(HEADER_DIR), $(HEADER))

SRC_DIR			= ./src/
SRC				= 	main.c \
					utils/ft_isdigit.c \
					utils/ft_atoi.c \
					utils/convert_args.c \
					validation/validation_utils.c
SRC_PATH		= $(addprefix $(SRC_DIR), $(SRC))

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -pthread

BIN				= ./bin/
BINARY_OUT		= $(addprefix $(BIN), $(NAME))

all: $(BINARY_OUT)

$(BINARY_OUT): $(SRC_PATH) $(HEADER_PATH)
	@ mkdir -p $(BIN)
	@ $(CC) $(CFLAGS) $(SRC_PATH) -I $(HEADER_DIR) -o $(NAME)
	@ mv $(NAME) $(BIN)
	@ echo "$(NAME) compiled successfully!"

#clean:
#	@ $(MAKE) clean -C $(LIBFT_DIR)
#	@ echo "libft object files erased successfully!"

fclean: clean
	@ rm -f $(BINARY_OUT)
	@ rm -rf $(BIN)
	@ echo "$(NAME) binaries erased successfully!"

re: fclean all

leaks:
	@ mkdir -p $(BIN)
	@ $(CC) $(CFLAGS) -g $(SRC_PATH) -I $(HEADER_DIR) -I $(HEADER_LIBFT) -o $(NAME)
	@ mv $(NAME) $(BIN)
	@ echo "$(NAME) with leak check option compiled successfully!"

simple:
	@ mkdir -p $(BIN)
	@ $(CC) -g $(SRC_PATH) -I $(HEADER_DIR) -I $(HEADER_LIBFT) -o $(NAME)
	@ mv $(NAME) $(BIN)
	@ echo "$(NAME) without compile flags compiled successfully!"

.PHONY: all clean fclean re
