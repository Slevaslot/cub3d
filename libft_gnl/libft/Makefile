# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:18 by pdosso-d          #+#    #+#              #
#    Updated: 2023/11/20 15:11:35 by pdosso-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_freetab.c \
		ft_tab_size.c \

OBJS = ${SRCS:.c=.o}

SRCSBONUS =	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJSBONUS	= ${SRCSBONUS:.c=.o}

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

$(NAME): $(OBJS)
			ar rcs ${NAME} $(OBJS)


bonus: ${OBJS} ${OBJSBONUS}
			ar rcs ${NAME} ${OBJS} ${OBJSBONUS}

clean:
			${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
			${RM} ${NAME}

re: fclean all


.PHONY:		bonus all clean fclean re
