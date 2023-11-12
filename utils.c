/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:37:28 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/12 14:27:30 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_error(char *err_message, t_data *data)
{
	free_all(data);
	printf("Error : %s", err_message);
	exit(2);
}

void	map_print(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		dprintf(2, "%s\n", str[i]);
}

void	free_all(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free_tab(data->map);
	free_tab(data->textures);
	free(data->mlx_ptr);
}
