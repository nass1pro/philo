# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 15:15:06 by nahaddac          #+#    #+#              #
#    Updated: 2021/01/09 17:52:20 by nahaddac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= main.c ft_atoi.c init.c clear_all.c eat.c message.c fork.c\
				  ft_error.c utils.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O2 -Wall -Wextra -Werror -g
LIBS			= -lpthread

NAME			= philo_two

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
