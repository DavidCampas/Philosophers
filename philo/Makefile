NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

SRCS =	main.c\
		init.c\
		monitor.c \
		routine.c\
		threads.c\
		utils.c

HEADER = philo.h

OBJS = ${SRCS:.c=.o}
		
# Build everything
all: $(NAME)

# Compile .c to .o
%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

# Build the program
$(NAME): $(OBJS) Makefile $(HEADER)
	@${CC} ${CFLAGS} $(OBJS) -o ${NAME}

# Clean objects
clean:
	@${RM} ${OBJS}

# Clean all files
fclean: clean
	@${RM} ${NAME}

# Rebuild project
re: fclean all

.PHONY: all clean fclean re