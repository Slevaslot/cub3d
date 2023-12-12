/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:37:28 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 15:08:59 by aproust          ###   ########.fr       */
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

void	free2(t_data *data)
{
	if (data->f_color)
		free(data->f_color);
	if (data->c_color)
		free(data->c_color);
	free_tab(data->file);
	free_tab(data->map);
	free_tab(data->txtr);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	free2(data);
	while (data->img && ++i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->img[i]);
		if (i == 3)
			free(data->img);
	}
	if (data->addr)
		free(data->addr);
	if (data->window)
		mlx_destroy_image(data->mlx_ptr, data->window);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}
