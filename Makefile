# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/14 18:18:18 by lbenedar          #+#    #+#              #
#    Updated: 2021/08/14 18:18:18 by lbenedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CFLAGS		=	-Werror -Wextra -Wall
OPTFLAGS	=	-O2
SRCS_DIR	=	srcs
INC_DIR		=	includes
INC			=	-I$(INC_DIR)
SRCS		=	$(SRCS_DIR)/philo.c \
				$(SRCS_DIR)/philo_utils.c \
				$(SRCS_DIR)/philo_thread.c \
				$(SRCS_DIR)/philo_setup.c \
				$(SRCS_DIR)/philo_output.c
OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
NORM		=	norminette
NORM_PATHS	=	$(SRCS_DIR)/*.c \
				$(INC_DIR)/*.h
RM			=	rm -rf

all:
	$(MAKE) $(NAME) -j 4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME) -pthread

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

norm:
	$(NORM) $(NORM_PATHS)

re: fclean all

%.o:%.c
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@ $(INC) -pthread

.PHONY: all bonus clean fclean re
