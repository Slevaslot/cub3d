PROG	= cub3d
SRCS 	= main.c key.c\

OBJS 	= $(addprefix obj/,${SRCS:.c=.o} ${SRCS_LIBFT:.c=.o})
LIBS = minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm

CFLAGS 	= #-Wall -Wextra -Werror
CC 		= gcc

obj/%.o: %.c
	gcc ${CFLAGS} -g3 -c $< -o $@

all: 		${PROG}

${PROG}:	${OBJS}
					@make -C minilibx-linux/
					@$(CC) ${OBJS} ${LIBS} -o ${PROG}
					@echo "cub3d Compiled!\n"


bonus:		${PROG_B}

${PROG_B}:	${OBJS_B}

					@echo "\cub3d Bonus Compiled! \n"

clean:

					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@rm -f $(NAME)
					@rm -f ${PROG}
					@echo "\nDelete ALL!\n"

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re
