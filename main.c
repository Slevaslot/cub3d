/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/27 16:04:56 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_data *data)
{
	int	w;
	int	h;
	int	pixel_bits;
	int	line_bytes;
	int	edian;

	data->addr = ft_calloc(sizeof(char *), 5);
	data->img = ft_calloc(sizeof(void *), 5);
	data->img[0] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[0], &w, &h);
	data->img[1] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[1], &w, &h);
	data->img[2] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[2], &w, &h);
	data->img[3] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[3], &w, &h);
	data->addr[0] = mlx_get_data_addr(data->img, *pixel_bits, *line_bytes, NULL);
	data->addr[1] = mlx_get_data_addr(data->img, NULL, *line_bytes, NULL);
	data->addr[2] = mlx_get_data_addr(data->img, NULL, *line_bytes, NULL);
	data->addr[3] = mlx_get_data_addr(data->img, NULL, *line_bytes, NULL);
}

void	found_player_dir(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	else if (data->player_dir == 'S')
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
	else if (data->player_dir == 'E')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (data->player_dir == 'W')
	{
		data->dirX = 0;
		data->dirY = -1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
}

int	ez(int key, t_data *data)
{
	if (key == 65293)
		raytracing(data);
	return (0);
}

int	start_program(char *map_name, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1016, "Cub3d");
	map_init(data, map_name);
	found_player_dir(data);
	get_texture(data);
	mlx_loop_hook(data->mlx_ptr, raytracing, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop(data->mlx_ptr);
	return (1);
}

int	exit_all(void)
{
	exit(0);
}

int	check_arg(char *av)
{
	int	i;

	i = -1;
	while (av[++i])
		;
	if (av[i - 4] == '.' && av[i - 3] == 'c' && av[i - 2] == 'u'
		&& av[i - 1] == 'b')
		return (0);
	return (printf("Error : Invalid file format\n"), 1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		if (check_arg(av[1]))
			return (1);
		data.file = 0;
		data.key_pressed = 0;
		data.f_color = 0;
		data.c_color = 0;
		data.map = 0;
		data.txtr = ft_calloc(sizeof(char *), 7);
		if (!data.txtr)
			return (1);
		if (start_program(av[1], &data) < 0)
			return (exit_all());
		// draw_minimap(&data);

	}
	else
		return (printf("Error : too much parameter\n"), 1);
}
