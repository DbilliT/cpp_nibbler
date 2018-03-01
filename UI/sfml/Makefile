##
## Makefile for Makefile in /home/bechad_p/rendu/cpp_nibbler/UI/sfml
## 
## Made by Pierre Bechade
## Login   <bechad_p@epitech.net>
## 
## Started on  Mon Mar 30 15:08:32 2015 Pierre Bechade
## Last update Sun Apr  5 18:49:37 2015 Pierre Bechade
##

NAME		=	lib_nibbler_sfml.so

CXXFLAGS	+=	-Wextra -Wall -W -fPIC -ldl -fPIC $(INCS) -std=c++11

INCS		=	-I./
INCS		+=	-I../../project/INibblerDisplay
INCS		+=	-I../../project/object
INCS		+=	-I../../project/game
INCS		+=	-I../../project/exception
INCS		+=	-I../../project/nibbler
INCS		+=	-I./SFML-2.2/include
INCS 		+=	-Iinc

LDFLAGS		+=	-shared $(LIB)

LIB 		=	-lsfml-graphics -lsfml-window -lsfml-system -L./SFML-2.2/lib $(INCS)

SRCS		=	ui_sfml.cpp

OBJS 		=	$(SRCS:.cpp=.o)

CXX		=	g++ 

all:			$(NAME)


$(NAME):		$(OBJS)
			$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS) 
			cp $(NAME) ../../.

clean:
			rm -f $(OBJS)


fclean:			clean
			rm -f $(NAME)
			rm -f ../../$(NAME)


re:			fclean all

.PHONY:			all clean fclean re
