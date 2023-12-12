/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:48:03 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 17:06:43 by slevaslo         ###   ########.fr       */
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
		if (data->map[(int)((data->posx - data->diry * movespeed - 0.000001))]
			[(int)(data->posy)] != '1')
			data->posx -= data->diry * movespeed - 0.000001;
		if (data->map[(int)(data->posx)]
			[((int)(data->posy + data->dirx * movespeed - 0.000001))] != '1')
			data->posy += data->dirx * movespeed - 0.000001;
	}
	else if (key == 119)
	{
		if (data->map[(int)(data->posx + data->dirx * movespeed - 0.000001)]
			[(int)(data->posy - 0.000001)] != '1')
			data->posx += data->dirx * movespeed;
		if (data->map[(int)(data->posx - 0.000001)]
			[((int)(data->posy + data->diry * movespeed - 0.000001))] != '1')
			data->posy += data->diry * movespeed;
	}
}

void	movement_key_left_right(int key, t_data *data, double movespeed)
{
	if (key == 115)
	{
		if (data->map[(int)((data->posx - data->dirx * movespeed - 0.000001))]
			[(int)(data->posy - 0.000001)] != '1')
			data->posx -= data->dirx * movespeed;
		if (data->map[(int)(data->posx - 0.000001)]
			[((int)(data->posy - data->diry * movespeed - 0.000001))] != '1')
			data->posy -= data->diry * movespeed;
	}
	else if (key == 100)
	{
		if (data->map[(int)((data->posx + data->diry * movespeed - 0.000001))]
			[(int)(data->posy)] != '1')
			data->posx += data->diry * movespeed - 0.000001;
		if (data->map[(int)(data->posx)]
			[((int)(data->posy - data->dirx * movespeed - 0.000001))] != '1')
			data->posy -= data->dirx * movespeed - 0.000001;
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
	data->oldplanex = data->planex;
	olddirx = data->dirx;
	if (key == 65363)
	{
		data->dirx = data->dirx * cos(-rs) - data->diry * sin(-rs);
		data->diry = olddirx * sin(-rs) + data->diry * cos(-rs);
		data->planex = data->planex * cos(-rs) - data->planey * sin(-rs);
		data->planey = data->oldplanex * sin(-rs) + data->planey * cos(-rs);
	}
	if (key == 65361)
	{
		data->dirx = data->dirx * cos(rs) - data->diry * sin(rs);
		data->diry = olddirx * sin(rs) + data->diry * cos(rs);
		data->planex = data->planex * cos(rs) - data->planey * sin(rs);
		data->planey = data->oldplanex * sin(rs) + data->planey * cos(rs);
	}
	else
		movement_key_left_right(key, data, movespeed);
	return (0);
}
