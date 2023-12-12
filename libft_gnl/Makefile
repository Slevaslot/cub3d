# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 15:46:35 by pdosso-d          #+#    #+#              #
#    Updated: 2023/12/12 17:46:26 by slevaslo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM              =	rm -f

NAME            =	libft_gnl.a

LIBRARIES	=	get_next_line/libget_next_line.a\
			libft/libft.a

all:            $(NAME)

$(NAME):
				make -C libft
				make -C get_next_line
				ar rcsT $(NAME) $(LIBRARIES)

clean:
				make -C libft clean
				make -C get_next_line clean


fclean:         clean
				make -C libft fclean
				make -C get_next_line fclean
				$(RM) $(NAME)


re:             fclean $(NAME)

bonus:			re

.PHONY:			all clean fclean re bonus
