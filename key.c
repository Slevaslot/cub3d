#include "cub3d.h"

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int	del_key(int key, t_data *data)
{
	if (key == 65307)
	{
		free_all(data);
		exit(0);
	}
	return (0);
}
