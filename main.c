/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/08 19:12:13 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_program(char *map_name, t_data *data)
{
	int	i;

	i = -1;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (-1);
	data->buff = (int **)ft_calloc(sizeof(int *), (HEIGHT + 1));
	while (++i < HEIGHT + 1)
		data->buff[i] = (int *)ft_calloc(sizeof(int), (WIDTH + 1));
	map_init(data, map_name);
	found_player_dir(data);
	if (check_texture(data))
		return (printf("Error: texture file does not exist\n"),
			free_all(data), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	data->image_mini = mlx_new_image(data->mlx_ptr, 100, 100);
	data->window = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->win_addr = mlx_get_data_addr(data->window, &data->pixel_bits[0],
			&data->line_bytes[0], &data->edian[0]);
	get_texture(data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key, data);
	mlx_loop_hook(data->mlx_ptr, init_raytracing, data);
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
		data.addr = 0;
		data.img = 0;
		data.window = 0;
		data.image_mini = 0;
		data.win_ptr = 0;
		data.txtr = ft_calloc(sizeof(char *), 7);
		if (!data.txtr)
			return (1);
		if (start_program(av[1], &data) < 0)
			return (exit_all());
	}
	else
		return (printf("Error : too much parameter\n"), 1);
}
