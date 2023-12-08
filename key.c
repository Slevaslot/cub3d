/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by aproust           #+#    #+#             */
/*   Updated: 2023/12/08 15:53:52 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

void	movement_key_front_back(int key, t_data *data, double movespeed)
{
	if (key == 65307)
	{
		free_all(data);
		exit(0);
	}
	else if (key == 97)
	{
		if (data->map[(int)((data->posx - data->dirY * movespeed - 0.000001))]
			[(int)(data->posy)] != '1')
			data->posx -= data->dirY * movespeed - 0.000001;
		if (data->map[(int)(data->posx)]
			[((int)(data->posy + data->dirX * movespeed - 0.000001))] != '1')
			data->posy += data->dirX * movespeed - 0.000001;
	}
	else if (key == 119)
	{
		if (data->map[(int)(data->posx + data->dirX * movespeed - 0.000001)]
			[(int)(data->posy - 0.000001)] != '1')
			data->posx += data->dirX * movespeed;
		if (data->map[(int)(data->posx - 0.000001)]
			[((int)(data->posy + data->dirY * movespeed - 0.000001))] != '1')
			data->posy += data->dirY * movespeed;
	}
}

void	movement_key_left_right(int key, t_data *data, double movespeed)
{
	if (key == 115)
	{
		if (data->map[(int)((data->posx - data->dirX * movespeed - 0.000001))]
			[(int)(data->posy - 0.000001)] != '1')
			data->posx -= data->dirX * movespeed;
		if (data->map[(int)(data->posx - 0.000001)]
			[((int)(data->posy - data->dirY * movespeed - 0.000001))] != '1')
			data->posy -= data->dirY * movespeed;
	}
	else if (key == 100)
	{
		if (data->map[(int)((data->posx + data->dirY * movespeed - 0.000001))]
			[(int)(data->posy)] != '1')
			data->posx += data->dirY * movespeed - 0.000001;
		if (data->map[(int)(data->posx)]
			[((int)(data->posy - data->dirX * movespeed - 0.000001))] != '1')
			data->posy -= data->dirX * movespeed - 0.000001;
	}
	else
		movement_key_front_back(key, data, movespeed);
}

int	key(int key, t_data *data)
{
	double	olddirx;
	double	movespeed;
	double	rs;

	rs = 0.042;
	movespeed = 0.083;
	data->oldplanex = data->planeX;
	olddirx = data->dirX;
	if (key == 65363)
	{
		data->dirX = data->dirX * cos(-rs) - data->dirY * sin(-rs);
		data->dirY = olddirx * sin(-rs) + data->dirY * cos(-rs);
		data->planeX = data->planeX * cos(-rs) - data->planeY * sin(-rs);
		data->planeY = data->oldplanex * sin(-rs) + data->planeY * cos(-rs);
	}
	if (key == 65361)
	{
		data->dirX = data->dirX * cos(rs) - data->dirY * sin(rs);
		data->dirY = olddirx * sin(rs) + data->dirY * cos(rs);
		data->planeX = data->planeX * cos(rs) - data->planeY * sin(rs);
		data->planeY = data->oldplanex * sin(rs) + data->planeY * cos(rs);
	}
	else
		movement_key_left_right(key, data, movespeed);
	return (0);
}
