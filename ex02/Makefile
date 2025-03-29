# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: <yourname> <yourmail@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 00:00:00 by <yourname>        #+#    #+#              #
#    Updated: 2023/03/01 00:00:00 by <yourname>       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= PmergeMe
CXX		= c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98 -g

SRCS	= main.cpp \
		  PmergeMe.cpp

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
