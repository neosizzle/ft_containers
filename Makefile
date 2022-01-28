SRCS = ./srcs/*.cpp
OBJS = *.o
INCS = ./incs
NAME = a.out
# CC = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
CC = c++ -Wall -Wextra -std=c++98 -fsanitize=address -g3

all : ${NAME}

${NAME} : ${SRCS} ${INCS}
	${CC} -c -I${INCS} ${SRCS}
	${CC} ${OBJS} -o ${NAME}

clean :
	rm -rf ${OBJS}

fclean :
	rm -rf ${OBJS}
	rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re bonus