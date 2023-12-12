/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 17:37:34 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data, int x)
{
	int		y;
	int		color;

	find_wall(data);
	data->lineheight = (int)(HEIGHT / data->perpwalldist);
	draw_value_init(data);
	data->texpos = (data->drawstart - HEIGHT
			/ 2 + data->lineheight / 2) * data->step;
	y = -1;
	while (++y < data->drawstart)
		put_ceiling_in_window(data, x, y);
	while (++y < data->drawend)
	{
		data->texy = (int)data->texpos & (64 - 1);
		data->texpos += data->step;
		color = data->addr[data->texdir][64 * data->texy + data->texx];
		if (data->side == 1)
			color = (color >> 1) & 8355711;
		ft_memcpy(&data->win_addr[y * data->line_bytes[0]
			+ x * (data->pixel_bits[0] / 8)], &color, 4);
	}
	y = data->drawend;
	while (++y < HEIGHT)
		put_floor_in_window(data, x, y);
}

void	init_raycasting_sequel(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->posx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->posx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->posy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->posy) * data->deltadisty;
	}
}

int	init_raycasting(t_data *data)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		data->camerax = 2 * x / (double)WIDTH - 1;
		data->raydirx = data->dirx + data->planex * data->camerax;
		data->raydiry = data->diry + data->planey * data->camerax;
		data->mapx = (int)data->posx;
		data->mapy = (int)data->posy;
		data->deltadistx = fabs(1 / data->raydirx);
		data->deltadisty = fabs(1 / data->raydiry);
		init_raycasting_sequel(data);
		raycasting(data, x);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
	return (1);
}
