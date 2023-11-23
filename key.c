/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by aproust           #+#    #+#             */
/*   Updated: 2023/11/23 15:22:36 by aproust          ###   ########.fr       */
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

	rotSpeed = 0.0166 * 3.0;
	moveSpeed = 0.0166 * 5.0;
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
	else if (key == 115)
	{
		if (data->map[(int)(data->posX - data->dirX * moveSpeed)][(int)(data->posY - data->dirY * moveSpeed)] != '1')
		{
			data->posX -= data->dirX * moveSpeed;
			data->posY -= data->dirY * moveSpeed;
		}
	}
	else if (key == 119)
	{
		if(data->map[(int)(data->posX + data->dirX * moveSpeed)][(int)(data->posY + data->dirY * moveSpeed)] != '1')
		{
			data->posX += data->dirX * moveSpeed;
			data->posY += data->dirY * moveSpeed;
		}
	}
	raytracing(data);
	return (0);
}

	/* if (key == 65361)
		rotate_left(data);
	if (key == 65363)
		rotate_right(data);
	browse_image(data); */
