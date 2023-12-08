/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/08 15:22:54 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_data *data)
{
	data->img = ft_calloc(sizeof(void *), 5);
	data->img[0] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[0], &data->w[0], &data->h[0]);
	data->img[1] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[1], &data->w[1], &data->h[1]);
	data->img[2] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[2], &data->w[2], &data->h[2]);
	data->img[3] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[3], &data->w[3], &data->h[3]);
	data->addr = (int **)ft_calloc(sizeof(int *), 5);
	data->addr[0] = (int *)mlx_get_data_addr(data->img[0], &data->pixel_bits[1], &data->line_bytes[1], &data->edian[1]);
	data->addr[1] = (int *)mlx_get_data_addr(data->img[1], &data->pixel_bits[2], &data->line_bytes[2], &data->edian[2]);
	data->addr[2] = (int *)mlx_get_data_addr(data->img[2], &data->pixel_bits[3], &data->line_bytes[3], &data->edian[3]);
	data->addr[3] = (int *)mlx_get_data_addr(data->img[3], &data->pixel_bits[4], &data->line_bytes[4], &data->edian[4]);
}

int	check_texture(t_data *data)
{
	int	fd[4];

	fd[0] = open(data->txtr[0], 0);
	if (fd[0] < 0)
		return (1);
	fd[1] = open(data->txtr[1], 0);
	if (fd[1] < 0)
		return (close(fd[0]), 1);
	fd[2] = open(data->txtr[2], 0);
	if (fd[2] < 0)
		return (close(fd[0]), close(fd[1]), 1);
	fd[3] = open(data->txtr[3], 0);
	if (fd[3] < 0)
		return (close(fd[0]), close(fd[1]), close(fd[2]), 1);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (0);
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
	int i;

	i = -1;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	data->buff = (int **)ft_calloc(sizeof(int *), (HEIGHT + 1));
	while (++i < HEIGHT + 1)
		data->buff[i] = (int *)ft_calloc(sizeof(int), (WIDTH + 1));
	map_init(data, map_name);
	found_player_dir(data);
	if (check_texture(data))
		return (printf("Error: texture file does not exist\n"), free_all(data), 1);
	data->image_mini = mlx_new_image(data->mlx_ptr, 100, 100);
	data->window = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->win_addr = mlx_get_data_addr(data->window, &data->pixel_bits[0], &data->line_bytes[0], &data->edian[0]);
	get_texture(data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key, data);
	mlx_loop_hook(data->mlx_ptr, raytracing, data);
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
		data.txtr = ft_calloc(sizeof(char *), 7);
		if (!data.txtr)
			return (1);
		if (start_program(av[1], &data) < 0)
			return (exit_all());
	}
	else
		return (printf("Error : too much parameter\n"), 1);
}
