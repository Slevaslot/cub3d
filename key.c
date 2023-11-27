/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by aproust           #+#    #+#             */
/*   Updated: 2023/11/27 16:07:10 by aproust          ###   ########.fr       */
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
	// printf("dirx:%f, diry:%f\nplaneX:%f, planeY:%f\n", data->dirX, data->dirY, data->planeX, data->planeY);
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
		if(data->map[(int)(data->posX + data->dirX * moveSpeed)][(int)(data->posY + data->dirY * moveSpeed)] != '1')
		{
			data->posX += data->dirX * moveSpeed;
			data->posY += data->dirY * moveSpeed;
		}
	}
	else if (key == 115)
	{
		if (data->map[(int)(data->posX - data->dirX * moveSpeed)][(int)(data->posY - data->dirY * moveSpeed)] != '1')
		{
			data->posX -= data->dirX * moveSpeed;
			data->posY -= data->dirY * moveSpeed;
		}
	}
	else if (key == 100)
	{
		if (data->map[(int)(data->posX + data->dirY * moveSpeed)][(int)(data->posY - data->dirX * moveSpeed)] != '1')
		{
			data->posX += data->dirY * moveSpeed;
			data->posY -= data->dirX * moveSpeed;
		}
	}
	else if (key == 97)
	{
		if (data->map[(int)(data->posX - data->dirY * moveSpeed)][(int)(data->posY + data->dirX * moveSpeed)] == '0')
		{
			data->posX -= data->dirY * moveSpeed;
			data->posY += data->dirX * moveSpeed;
		}
	}
	// raytracing(data);
	return (0);
}

	/* if (key == 65361)
		rotate_left(data);
	if (key == 65363)
		rotate_right(data);
	browse_image(data); */
