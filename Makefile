SRCS = ./srcs/*.cpp
OBJS = *.o
# INCS = -I./incs -I./incs/Map -I./incs/Set
INCS = ./incs 
INCS_MAP = ./incs/Map
INCS_SET = ./incs/Set
INCS_VECT = ./incs/Vect
INCS_STACK = ./incs/Stack
NAME = a.out
# CC = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
CC = c++ -Wall -Wextra -std=c++98 -fsanitize=address -g3

all : ${NAME}

${NAME} : ${SRCS} ${INCS}
	${CC} -c -I${INCS} -I${INCS_MAP} -I${INCS_SET} -I${INCS_VECT} -I${INCS_STACK} ${SRCS}
	${CC} ${OBJS} -o ${NAME}

clean :
	rm -rf ${OBJS}

fclean :
	rm -rf ${OBJS}
	rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re bonus