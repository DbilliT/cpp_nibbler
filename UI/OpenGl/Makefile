##
## Makefile for Makefile in /home/bechad_p/rendu/cpp_nibbler/UI/sfml
## 
## Made by Pierre Bechade
## Login   <bechad_p@epitech.net>
## 
## Started on  Mon Mar 30 15:08:32 2015 Pierre Bechade
## Last update Sun Apr  5 18:48:51 2015 Pierre Bechade
##

NAME		=	lib_nibbler_opengl.so

CXXFLAGS	+=	-Wextra -Wall -W -fPIC -ldl -fPIC $(INCS) -std=c++11

INCS		=	-I./
INCS		+=	-I./../sfml/SFML-2.2/include/
INCS		+=	-I../../project/INibblerDisplay
INCS		+=	-I../../project/object
INCS		+=	-I../../project/game
INCS		+=	-I../../project/exception
INCS		+=	-I../../project/nibbler
INCS		+=	-Iinc

LDFLAGS		+=	-shared $(LIB)

LIB 		=	`sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -lSDL_mixer -lGL -lGLU $(INCS)

SRCS		=	uiOpenGl.cpp

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
