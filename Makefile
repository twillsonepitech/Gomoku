# START of Makefile color and typo of messages

_END='\033[0m'
_GREEN='\033[32m'

# END	of Makefile color and typo of messages

CXX	=	g++

RM	?=	rm -rf

NAME	=	gomoku

ARCHIVER	=	ar

TESTS_BIN	:=	*.gc*
TESTS_BIN_NAME	:=	unit_tests
TESTS_LIBS	:=	-lcriterion --coverage

CXXFLAGS	+=	-std=c++2a -Wall -Wextra -Werror -fPIC -pedantic

CPPFLAGS	+=	-iquote ./includes

MAIN	=	${addsuffix .cpp, ${addprefix ./, Main }}
SRCS	=	${addsuffix .cpp, ${addprefix ./srcs/, Board Minimax }}
BLTS	=	${addsuffix .cpp, ${addprefix ./srcs/builtins/, }}

ALL_SRCS	:=	${MAIN}
ALL_SRCS	+=	${SRCS}
ALL_SRCS	+=	${BLTS}

TESTS_SRCS	:=	${SRCS}
TESTS_SRCS	+=	${addsuffix .cpp, ${addprefix ./tests/tests_, }}

OBJS	=	${ALL_SRCS:.cpp=.o}
TESTS_OBJS	:=	${TESTS_SRCS:.cpp=.o}

%.o : %.cpp
	@$ ${CXX} ${CXXFLAGS} ${CPPFLAGS} -c $< -o $@
	@echo "${CXX} ${CXXFLAGS} ${CPPFLAGS} -c $< -o $@ ["${_GREEN}"OK"${_END}"]"
.SUFFIXES: .o .cpp

all:	${NAME}

${NAME}:	${OBJS}
	@${CXX} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}
	${RM} ${NAME}
	${RM} ${NAME:.so=.a}
	${RM} logs.out

fclean:	clean
	${RM} ${TESTS_OBJS}
	${RM} ./${TESTS_BIN}
	${RM} ./tests/${TESTS_BIN}
	${RM} ${TESTS_BIN_NAME}

re:	fclean all

debug:	CXXFLAGS	+=	-g3
debug:	re

tests_run:	${TESTS_OBJS}
	${CXX} ${TESTS_LIBS} ${TESTS_OBJS} -o ${TESTS_BIN_NAME}
	./${TESTS_BIN_NAME}
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}

valgrind:	CXXFLAGS	+=	-g3
valgrind:	${TESTS_OBJS}
	${CXX} ${TESTS_LIBS} ${TESTS_OBJS} -o ${TESTS_BIN_NAME}
	valgrind --trace-children=yes ./${TESTS_BIN_NAME}
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}

.PHONY:	all clean fclean re debug tests_run valgrind
