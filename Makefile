# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2017/03/25 19:49:14 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Abstract_vm

# Dir vars

SRCDIR = src

INCLUDESDIR = includes

# Files vars

MAIN = main.cpp

CFILES = FactoryOperand.class.cpp Parser.class.cpp

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

OBJ = $(SRC:.cpp=.o) $(MAIN:.cpp=.o)

HFILES = IOperand.class.hpp Operand.class.hpp FactoryOperand.class.hpp \
	Parser.class.hpp MyExceptions.class.hpp

HEADERS = $(patsubst %, $(INCLUDESDIR)/%, $(HFILES))

# COMPILATION

# ERRORFLAGS = -Wall -Werror -Wextra -march=native -Ofast
ERRORFLAGS = --std=c++11 -march=native -O2

INCLUDEFLAGS = -I $(INCLUDESDIR)/

FLAGS = $(ERRORFLAGS) $(INCLUDEFLAGS)

CC = clang++

# Git vars

TOGIT =	$(SRC) \
		$(HEADERS) \
		$(MAIN) \
		Makefile \
		auteur \

# Rules

all: $(NAME)

$(NAME): $(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

re: fclean all

clean:
			@rm -f $(OBJ)

fclean: clean
			@rm -f $(NAME)

%.o: %.cpp
			$(CC) -o $@ -c $< $(FLAGS)

git:
		git add $(TOGIT)
		git commit -m 'auto update'
		git push
