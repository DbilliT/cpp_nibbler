##
## Makefile for Makefile in /home/bechad_p/rendu/cpp_nibbler
## 
## Made by Pierre Bechade
## Login   <bechad_p@epitech.net>
## 
## Started on  Thu Mar 26 11:16:22 2015 Pierre Bechade
## Last update Sun Apr  5 12:00:08 2015 Pierre Bechade
##

CXX		=	g++

RM		=	rm -f

CXXFLAGS	=	-W -Wall -Werror -pthread -std=c++11

LDFLAGS		=	-ldl -Wl,-E -pthread

CXXFLAGS	+=	-I./project/nibbler/.
CXXFLAGS	+=	-I./project/exception/.
CXXFLAGS	+=	-I./project/object/.
CXXFLAGS	+=	-I./project/game/.
CXXFLAGS	+=	-I./project/INibblerDisplay/.

NAME		=	bin_nibbler

NAME_SCRIPT	=	nibbler

SRCS		=	project/nibbler/nibbler.cpp	\
			project/object/object.cpp	\
			project/game/game.cpp

OBJS		=	$(SRCS:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)
			make -C UI/sfml/
			make -C UI/ncurses/
			make -C UI/OpenGl/
			@echo -e "#!/bin/sh" > nibbler
			@echo -n "export LD_LIBRARY_PATH=/usr/lib64/mpi/gcc/openmpi/lib64:./UI/sfml/SFML-2.2/lib/ && ./bin_nibbler $$" >> $(NAME_SCRIPT)
			@echo -n "1 $$" >> $(NAME_SCRIPT)
			@echo -n "2 $$" >> $(NAME_SCRIPT)
			@echo -n "3 $$" >> $(NAME_SCRIPT)
			@echo -n "4" >> $(NAME_SCRIPT)
			chmod 744 $(NAME_SCRIPT)

clean:
			$(RM) $(OBJS)
			make clean -C UI/sfml/
			make clean -C UI/ncurses/
			make clean -C UI/OpenGl/

fclean:			clean
			$(RM) $(NAME) $(NAME_SCRIPT)
			make fclean -C UI/sfml/
			make fclean -C UI/ncurses/
			make fclean -C UI/OpenGl/

re:			fclean all
			make re -C UI/sfml/
			make re -C UI/ncurses/
			make re -C UI/OpenGl/

.PHONY:			fclean clean all
