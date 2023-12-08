/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by aproust           #+#    #+#             */
/*   Updated: 2023/12/08 15:22:59 by aproust          ###   ########.fr       */
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
		if(data->map[(int)(data->posx + data->dirX * moveSpeed - 0.000001)]
			[(int)(data->posy - 0.000001)] != '1')
			data->posx += data->dirX * moveSpeed;
		if (data->map[(int)(data->posx - 0.000001)]
			[((int)(data->posy + data->dirY * moveSpeed - 0.000001))] != '1')
			data->posy += data->dirY * moveSpeed;
	}
	else if (key == 115)
	{
		if(data->map[(int)((data->posx - data->dirX * moveSpeed - 0.000001))]
			[(int)(data->posy - 0.000001)] != '1')
			data->posx -= data->dirX * moveSpeed;
		if (data->map[(int)(data->posx - 0.000001)]
			[((int)(data->posy - data->dirY * moveSpeed - 0.000001))] != '1')
			data->posy -= data->dirY * moveSpeed;
	}
	else if (key == 100)
	{
		if(data->map[(int)((data->posx + data->dirY * moveSpeed - 0.000001))]
			[(int)(data->posy)] != '1')
			data->posx += data->dirY * moveSpeed - 0.000001;
		if (data->map[(int)(data->posx)]
			[((int)(data->posy - data->dirX * moveSpeed - 0.000001))] != '1')
			data->posy -= data->dirX * moveSpeed - 0.000001;
	}
	else if (key == 97)
	{
		if(data->map[(int)((data->posx - data->dirY * moveSpeed - 0.000001))]
			[(int)(data->posy)] != '1')
			data->posx -= data->dirY * moveSpeed - 0.000001;
		if (data->map[(int)(data->posx)]
			[((int)(data->posy + data->dirX * moveSpeed - 0.000001))] != '1')
			data->posy += data->dirX * moveSpeed - 0.000001;
	}
	return (0);
}
