/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:44 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/15 02:27:09 by slevaslo         ###   ########.fr       */
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
	map_print(data->map);
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
		data.map = 0;
		data.textures = ft_calloc(sizeof(char *), 7);
		if (!data.textures)
			return (1);
		if (start_program(av[1], &data) < 0)
			return (exit_all());
		mlx_key_hook(data.win_ptr, del_key, &data);
		mlx_hook(data.win_ptr, 17, 0, close_window, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		return (printf("wrong parameter : ./cub3d map.cub\n"), 1);
}
