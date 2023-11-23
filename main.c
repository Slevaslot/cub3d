/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/23 15:38:33 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1980, 1080, "Cub3d");
	map_init(data, map_name);
	data->dirX = -1;
	mlx_key_hook(data->win_ptr, ez, data);
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
		data.dirX = -1;
		data.dirY = 0;
		data.planeX = 0;
		data.planeY = 0.66;
		data.textures = ft_calloc(sizeof(char *), 7);
		if (!data.textures)
			return (1);
		if (start_program(av[1], &data) < 0)
			return (exit_all());
		// draw_minimap(&data);

	}
	else
		return (printf("wrong parameter : ./cub3d map.cub\n"), 1);
}
