CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
LIB = ranlib
RM = rm -f

SRCS = *.c
INCS = libft.h

OBJS = ${SRCS:.c=.o}

NAME = libft.a

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}
	${LIB} ${NAME}

.c.o:
	${CC} ${CFLAGS} -I ${INCS} ${SRCS} -c

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
