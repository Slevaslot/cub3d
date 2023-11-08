#include "minilibx-linux/mlx.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct t_data
{
	int i;
	void	*mlx_ptr;
	void	*win_ptr;
	int		*mlx_img;

}t_data;

/* close key */

int	close_window(t_data *data);
int	del_key(int key, t_data *data);

