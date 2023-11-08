#ifndef CUB3D_H
# define CUB3D_H

#include "minilibx-linux/mlx.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "libft_gnl/libft_gnl.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct t_data
{
	int i;
	void	*mlx_ptr;
	void	*win_ptr;
	int		*mlx_img;
	char	**map;

}t_data;

/* close key */

int	close_error(int i);
int		close_window(t_data *data);
int		del_key(int key, t_data *data);
void	map_init(t_data *data, char *map_name);
void map_print(char **str);

#endif
