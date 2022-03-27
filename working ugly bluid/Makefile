
##
## EPITECH PROJECT, 2020
## Base
## File description:
## Main Makefile
##

##################### SRC #######################
SRC				=	src/Bluid.cpp

SRC				+=	src/main.cpp

#################### NAMES ######################
NAME			=	Bluid

##################### OBJ #######################
OBJ				=	$(SRC:.cpp=.o)

##################### FLAGS #####################
CXXFLAGS			=	-I include -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -Ofast

CXXFLAGS_DEBUG		=	-g

################## COMPILATION ##################
all:	$(NAME)

$(NAME):	$(OBJ)
	@(g++ $(OBJ) -o $(NAME) $(CXXFLAGS)) > /dev/null

debug:	CXXFLAGS += $(CXXFLAGS_DEBUG)
debug:	re

re:	fclean all

clean:
	@(rm -f $(OBJ)) > /dev/null
	@find . -name "*.o" -delete

fclean:	clean
	@rm -f $(NAME)
