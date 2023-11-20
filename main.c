/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/20 17:04:25 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_program(char *map_name, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "Cub3d");
	map_init(data, map_name);
	map_print(data->file);
	return (1);
}

int	exit_all(void)
{
	exit(0);
}

void	draw_minimap(t_data *data)
{
	float		x;
	float		y;

	y = 0;
	while (data->map[(int)y] != NULL)
	{
		x = 0;
		while (data->map[(int)y][(int)x] != '\0')
		{
			if (data->map[(int)y][(int)x] == '0') // Mur
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0xFFFFFF); // Blanc
			else if (data->map[(int)y][(int)x] == 'N' || data->map[(int)y][(int)x] == 'S' || data->map[(int)y][(int)x] == 'E' || data->map[(int)y][(int)x] == 'W') // Joueur
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0xFF0000); // Rouge
			else if (data->map[(int)y][(int)x] == '1') // Objet
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0x00FF00); // Vert
			else
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0x000000); // Noir (espace vide)
			x += 0.1;
		}
		y += 0.1;
	}
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
		data.map = 0;
		data.textures = ft_calloc(sizeof(char *), 7);
		if (!data.textures)
			return (1);
		if (start_program(av[1], &data) < 0)
			return (exit_all());
		draw_minimap(&data);
		mlx_key_hook(data.win_ptr, del_key, &data);
		mlx_hook(data.win_ptr, 17, 0, close_window, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		return (printf("wrong parameter : ./cub3d map.cub\n"), 1);
}
