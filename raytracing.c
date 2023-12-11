/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/12/11 14:24:40 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_minimap(t_data *d, double x, double y)
{
	int	color;

	if ((int)x == (int)d->posx && (int)y == (int)d->posy)
		color = 0xFF0000;
	else if (d->map[(int)x][(int)y] == '0'
		|| d->map[(int)x][(int)y] == 'N'
		|| d->map[(int)x][(int)y] == 'S'
		|| d->map[(int)x][(int)y] == 'E'
		|| d->map[(int)x][(int)y] == 'W')
		color = d->cf;
	else if (d->map[(int)x][(int)y] == '1')
		color = 0x606060;
	else
		color = 0x000000;
	return (color);
}

void	draw_minimap(t_data *d)
{
	float	x;
	float	y;
	int		color;
	int		pixel_index;

	x = 0;
	d->addrformini = mlx_get_data_addr(d->image_mini, &d->pixel_bits[5],
			&d->line_bytes[5], &d->edian[5]);
	while (d->map[(int)x] != NULL)
	{
		y = 0;
		while (d->map[(int)x][(int)y] != '\0')
		{
			pixel_index = (int)((x * d->line_bytes[5]
						/ (d->pixel_bits[5] / 8) * 10) + (y * 10));
			color = get_color_minimap(d, x, y);
			*(unsigned int *)(d->addrformini + pixel_index
					* (d->pixel_bits[5] / 8)) = color;
			y += 0.1;
		}
		x += 0.1;
	}
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->image_mini, 0, 0);
}

void	raytracing(t_data *data, int x)
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

void	init_raytracing_sequel(t_data *data)
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

int	init_raytracing(t_data *data)
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
		init_raytracing_sequel(data);
		raytracing(data, x);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
	return (1);
}
