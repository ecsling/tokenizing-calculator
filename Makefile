NAME := my_bc
CC := cc
CFLAGS := -Wall -Wextra -Werror -Iinclude

SRC := src/main.c src/error.c src/dynarray.c src/lexer.c src/shunting.c src/evaluator.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# address sanitizer
asan: CFLAGS += -g3 -fsanitize=address
asan: re

.PHONY: all clean fclean re asan

# Run the test harness (builds binary if needed)
test: all
	./tests/run_tests.sh

.PHONY: test