SRCS			= main.c error.c

OBJS			= $(SRCS:.c=.o)
NAME			= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread

RM				= rm -f

all: $(NAME)

.c.o:
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Compilation complete. Executable: $(NAME)"

clean:
	@echo "Cleaning up object files..."
	@$(RM) $(OBJS)

fclean: clean
	@echo "Cleaning up executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re