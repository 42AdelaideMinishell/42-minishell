CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBRARY = -lft

ROOT_DIR = ${shell pwd}
LIBFT_DIR = ${ROOT_DIR}/libft

SRCS = ./src/*.c
INCS = ./inc

NAME = minishell

${NAME}: all

all:
	@echo "Complie libft..."
	@make -C ${LIBFT_DIR}
	@${CC} ${CFLAGS} -I ${INCS} ${SRCS} -o ${NAME} -L${LIBFT_DIR} ${LIBRARY}
	@echo "./${NAME} Complie successfully"

clean:
	@echo "Delete library compile files..."
	@${RM} ${LIBFT_DIR}/*.o

fclean: clean
	@echo "Delete library files..."
	@${RM} ${LIBFT_DIR}/*.a
	@${RM} ${NAME}
	@echo "Delete execution files..."

re: fclean all

.PHONY: all clean fclean re