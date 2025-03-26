NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

OBJS = ${SRCS:.c=.o}

SRCS =	main.c\
		init.c\
		parsing.c\
		safe_funcions.c\
		utils.c\
		dinner.c

HEADER = philo.h

# Build everything
all: $(NAME)

# Compile .c to .o
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

# Build the program
$(NAME): $(OBJS) Makefile $(HEADER)
	${CC} ${CFLAGS} $(OBJS) -o ${NAME}

# Clean objects
clean:
	${RM} ${OBJS}

# Clean all files
fclean: clean
	${RM} ${NAME}

# Rebuild project
re: fclean all

.PHONY: all clean fclean re
