PROG	= cub3d
SRCS 	= main.c \
		  key.c \
		  utils.c \
		  map_init.c \
		  parsing.c \
		  parsing_sequel.c \
		  raytracing3.c\
		  truc.c \

OBJS 	= $(addprefix obj/,${SRCS:.c=.o} ${SRCS_LIBFT:.c=.o})
LIBS = minilibx-linux/libmlx_Linux.a libft_gnl/libft_gnl.a -lXext -lX11 -lm

CFLAGS 	= -Wall -Wextra -Werror
FOLDER_NAME = obj
CC 		= gcc

obj/%.o: %.c
	gcc ${CFLAGS} -g3 -c $< -o $@

all: 		${PROG}

${PROG}: create_folder ${OBJS}
					@make -C minilibx-linux/
					@make -C libft_gnl/
					@$(CC) ${OBJS} ${LIBS} -o ${PROG}
					@echo "cub3d Compiled!\n"


bonus:		${PROG_B}

create_folder:
	mkdir -p $(FOLDER_NAME)

${PROG_B}:	${OBJS_B}

					@echo "\cub3d Bonus Compiled! \n"

clean:

					@rm -f ${OBJS} ${OBJS_B}
					@make -C libft_gnl clean

fclean: 	clean
					@rm -f $(NAME)
					@rm -f ${PROG}
					@make -C libft_gnl fclean
					@echo "\nDelete ALL!\n"

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re
