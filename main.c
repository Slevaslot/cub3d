/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/24 18:12:31 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->win_ptr = mlx_new_window(data->mlx_ptr, 960, 540, "Cub3d");
	map_init(data, map_name);
	found_player_dir(data);
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
