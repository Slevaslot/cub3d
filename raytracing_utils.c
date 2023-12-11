/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:36:35 by aproust           #+#    #+#             */
/*   Updated: 2023/12/11 18:14:43 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_value_init(t_data *data)
{
	data->drawstart = -data->lineheight / 2 + HEIGHT / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + HEIGHT / 2;
	if (data->drawend >= HEIGHT)
		data->drawend = HEIGHT - 1;
	if (data->side == 0 && data->raydirx < 0)
		data->texdir = 1;
	else if (data->side == 0 && data->raydirx >= 0)
		data->texdir = 0;
	else if (data->side == 1 && data->raydiry < 0)
		data->texdir = 3;
	else if (data->side == 1 && data->raydiry >= 0)
		data->texdir = 2;
	if (data->side == 0)
		data->wallx = data->posy + data->perpwalldist * data->raydiry;
	else
		data->wallx = data->posx + data->perpwalldist * data->raydirx;
	data->wallx -= floor(data->wallx);
	data->step = 1.0 * 64 / data->lineheight;
	data->texx = (int)(data->wallx * (double)64);
	if (data->side == 0 && data->raydirx > 0)
		data->texx = 64 - data->texx - 1;
	if (data->side == 1 && data->raydiry < 0)
		data->texx = 64 - data->texx - 1;
}

void	find_wall(t_data *d)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		if (d->map[d->mapx][d->mapy] == '1')
			hit = 1;
	}
	if (d->side == 0)
		d->perpwalldist = (d->mapx - d->posx + (1 - d->stepx) / 2) / d->raydirx;
	else
		d->perpwalldist = (d->mapy - d->posy + (1 - d->stepy) / 2) / d->raydiry;
}

void	put_ceiling_in_window(t_data *data, int x, int y)
{
	data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)]
		= (data->cc);
	data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8) + 1]
		= (data->cc >> 8);
	data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8) + 2]
		= (data->cc >> 16);
}

void	put_floor_in_window(t_data *data, int x, int y)
{
	data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)]
		= (data->cf);
	data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8) + 1]
		= (data->cf >> 8);
	data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8) + 2]
		= (data->cf >> 16);
}
