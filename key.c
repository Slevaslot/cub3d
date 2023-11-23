/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by aproust           #+#    #+#             */
/*   Updated: 2023/11/22 18:24:09 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

void	rotate_left(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->map[++j])
	{
		while (data->map[j][++i])
		{
			if (data->map[j][i] == 'N')
			{
				data->map[j][i] = 'W';
				return ;
			}
			if (data->map[j][i] == 'W')
			{
				data->map[j][i] = 'S';
				return ;
			}
			if (data->map[j][i] == 'S')
			{
				data->map[j][i] = 'E';
				return ;
			}
			if (data->map[j][i] == 'E')
			{
				data->map[j][i] = 'N';
				return ;
			}
		}
		i = -1;
	}
}

void	rotate_right(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->map[++j])
	{
		while (data->map[j][++i])
		{
			if (data->map[j][i] == 'N')
			{
				data->map[j][i] = 'E';
				return ;
			}
			if (data->map[j][i] == 'E')
			{
				data->map[j][i] = 'S';
				return ;
			}
			if (data->map[j][i] == 'S')
			{
				data->map[j][i] = 'W';
				return ;
			}
			if (data->map[j][i] == 'W')
			{
				data->map[j][i] = 'N';
				return ;
			}
		}
		i = -1;
	}
}

int	del_key(int key, t_data *data)
{
	double	oldPlaneX;
	double	oldDirX;
	double	moveSpeed;
	double	rotSpeed;

	rotSpeed = 0.1 * 3.0;
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
		if (data->map[(int)data->posX - (int)data->dirX * (int)moveSpeed][(int)data->posY] != '1')
			data->posX -= data->dirX * moveSpeed;
		if (data->map[(int)data->posX][(int)data->posY - (int)data->dirY * (int)moveSpeed] != '1')
			data->posY -= data->dirY * moveSpeed;
	}
	else if (key == 119)
	{
		if(data->map[(int)data->posX + (int)data->dirX * (int)moveSpeed][(int)data->posY] != '1')
			data->posX += data->dirX * moveSpeed;
		if(data->map[(int)data->posX][(int)data->posY + (int)data->dirY * (int)moveSpeed] != '1')
			data->posY += data->dirY * moveSpeed;
	}
	raytracing(data);
	return (0);
}

	/* if (key == 65361)
		rotate_left(data);
	if (key == 65363)
		rotate_right(data);
	browse_image(data); */
