#include "cub3d.h"

int	start_program(char *map_name, t_data *data)
{
	int i = 0;
	(void)map_name;
	if (!(data->mlx_ptr = mlx_init()))
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "maps name :");
	return (1);
}

int	exit_all()
{
	return (0);
}


int main(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(data) * 1);
	if (ac == 2)
	{
		if (start_program(av[1], data) < 0)
			return (exit_all());
		mlx_key_hook(data->win_ptr, del_key, data);
		mlx_hook(data->win_ptr, 17, 0, close_window, data);
		mlx_loop(data->mlx_ptr);
	}
}
