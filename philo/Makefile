NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread 
#-fsanitize=thread
#-fsanitize=address


SRC = init.c main.c routine.c threads.c utils.c
OBJ = $(SRC:.c=.o)

ORANGE = $(shell tput setaf 202)
RED = $(shell tput setaf 1)
YELLOW = $(shell tput setaf 3)
BLUE = $(shell tput setaf 27)
GREEN = $(shell tput setaf 46)
RESET = $(shell tput sgr0)

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compiling philo OK$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
