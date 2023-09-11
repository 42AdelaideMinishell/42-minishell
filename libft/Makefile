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
	@${AR} ${NAME} ${OBJS}
	@${LIB} ${NAME}
	@echo "Libft create successfully"

.c.o:
	@${CC} ${CFLAGS} -I ${INCS} ${SRCS} -c

clean:
	@${RM} ${OBJS}
	@echo "Delete obj files successfully"

fclean: clean
	@${RM} ${NAME}
	@echo "Delete library file successfully"

re: fclean all

.PHONY: all clean fclean re
