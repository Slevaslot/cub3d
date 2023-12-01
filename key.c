/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by aproust           #+#    #+#             */
/*   Updated: 2023/12/01 18:48:06 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int	key(int key, t_data *data)
{
	double	oldPlaneX;
	double	oldDirX;
	double	moveSpeed;
	double	rotSpeed;

	rotSpeed = 0.042;
	moveSpeed = 0.083;
	oldPlaneX = data->planeX;
	oldDirX = data->dirX;
	if (key == 65307)
	{
		free_all(data);
		exit(0);
	}
	if (key == 65361)
	{
		data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
		data->dirY = oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
		data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
		data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
	}
	else if (key == 65363)
	{
		data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
		data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
		data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
		data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
	}
	else if (key == 119)
	{
		if(data->map[(int)(data->posx + data->dirX * moveSpeed)][(int)(data->posy + data->dirY * moveSpeed)] != '1')
		{
			data->posx += data->dirX * moveSpeed;
			data->posy += data->dirY * moveSpeed;
		}
	}
	else if (key == 115)
	{
		if (data->map[(int)(data->posx - data->dirX * moveSpeed)][(int)(data->posy - data->dirY * moveSpeed)] != '1')
		{
			data->posx -= data->dirX * moveSpeed;
			data->posy -= data->dirY * moveSpeed;
		}
	}
	else if (key == 100)
	{
		if (data->map[(int)(data->posx + data->dirY * moveSpeed)][(int)(data->posy - data->dirX * moveSpeed)] != '1')
		{
			data->posx += data->dirY * moveSpeed;
			data->posy -= data->dirX * moveSpeed;
		}
	}
	else if (key == 97)
	{
		if (data->map[(int)(data->posx - data->dirY * moveSpeed)][(int)(data->posy + data->dirX * moveSpeed)] != '1')
		{
			data->posx -= data->dirY * moveSpeed;
			data->posy += data->dirX * moveSpeed;
		}
	}
	// raytracing(data);
	return (0);
}
