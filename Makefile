##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile to compile
##

SRC	=	collisions.cpp					\
		$(DIR)*.cpp					\
		game/src/test.cpp					\
		engine/libs/Raylib/src/*.cpp	\
		engine/src/Application/*.cpp	\
		engine/src/Entities/*.cpp		\
		engine/src/Exception/*.cpp		\
		engine/src/Scenes/*.cpp			\
		engine/src/*.cpp

DIR	=	gamecore/src/

OBJ	=	$(SRC:.cpp=.o)

NAME	=	bomberman

CXX = g++ -g

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -g -Wall -Wextra -o $(NAME) $(SRC) -L ./ -lraylib -ldl -lpthread

clean:
	rm -f gamecore/src/*.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*

fclean:	clean
	rm -f $(NAME)

re:	fclean all