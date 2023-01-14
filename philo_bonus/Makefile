# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 17:13:34 by nlocusso          #+#    #+#              #
#    Updated: 2023/01/14 16:49:55 by nlocusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c parsing.c utils.c routine.c init.c free.c
OBJS		= ${SRCS:.c=.o}
NAME		= philo_bonus
CC			= clang -g -O0
CFLAGS		= -Wall -Wextra -Werror

all :        ${NAME}

.c.o :		${OBJS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -pthread

bonus :		${OBJS} 
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean :
			rm -f ${OBJS} ${BOBJS}

fclean :	clean
			rm -f ${NAME} 

re :
			make fclean
			make all

.PHONY : all clean fclean re bonus
