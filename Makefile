CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBRARY = -lft -lreadline

ROOT_DIR = ${shell pwd}
LIBFT_DIR = ${ROOT_DIR}/libft
RL_DIR = /usr/local/opt/readline/lib

SRCS = ./src/*.c
INCS = ./inc
RL_INCS = /usr/local/opt/readline/include/

NAME = minishell

${NAME}: all

all:
	@echo "Complie libft..."
	@make -C ${LIBFT_DIR}
	@${CC} ${CFLAGS} -I ${INCS} -I ${RL_INCS} ${SRCS} -o ${NAME} -L${LIBFT_DIR} -L$(RL_DIR) ${LIBRARY}
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