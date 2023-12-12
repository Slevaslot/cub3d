PROG	= cub3D
SRCS 	= main.c \
		  key.c \
		  utils.c \
		  map_init.c \
		  parsing.c \
		  parsing_sequel.c \
		  raycasting.c\
		  texture.c \
		  found_direction.c \
		  check_wall.c \
		  floor_and_ceiling.c \
		  check_rgb.c \
		  raycasting_utils.c\

OBJS 	= ${SRCS:.c=.o} ${SRCS_LIBFT:.c=.o}
LIBS = minilibx-linux/libmlx_Linux.a libft_gnl/libft_gnl.a -lXext -lX11 -lm
CFLAGS 	= -Wall -Wextra -Werror
FOLDER_NAME = obj
CC 		= gcc

all: 		${PROG}

%.o: %.c
	$(CC) ${CFLAGS} -g3 -c $< -o $@

${PROG}: 	${OBJS}
					make -C minilibx-linux/
					make -C libft_gnl/
					$(CC) ${OBJS} ${LIBS} -o ${PROG}

# create_folder:
# 	mkdir -p $(FOLDER_NAME)

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
