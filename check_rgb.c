/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:50:28 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 17:07:31 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_rgb_end(t_data *data, int param)
{
	if (data->check_rgb_number[0] < '0' || data->check_rgb_number[0] > '9')
		return (free(data->check_rgb_number), free(data->check_rgb_nb), 0);
	data->check_rgb_nb[++data->rgbj] = ft_atoi(data->check_rgb_number);
	if (data->check_rgb_nb[data->rgbj] > 255)
		return (free(data->check_rgb_number), 0);
	if (data->rgbj != 2)
		return (free(data->check_rgb_nb), free(data->check_rgb_number), 0);
	if (param == 0)
		data->f_color = data->check_rgb_nb;
	else if (param == 1)
		data->c_color = data->check_rgb_nb;
	return (free(data->check_rgb_number), 1);
}

int	check_rgb_fc(char *color, t_data *d, int param)
{
	while (color[++d->rgbi] && d->rgbj != 2)
	{
		if (color[d->rgbi] == ' ')
			continue ;
		else if (color[d->rgbi] == ',')
		{
			if (d->check_rgb_number[0] < '0' || d->check_rgb_number[0] > '9')
				return (free(d->check_rgb_number), free(d->check_rgb_nb), 0);
			d->check_rgb_nb[++d->rgbj] = ft_atoi(d->check_rgb_number);
			free(d->check_rgb_number);
			d->check_rgb_number = ft_calloc(sizeof(char), 1);
			if (d->check_rgb_nb[d->rgbj] < 0 || d->check_rgb_nb[d->rgbj] > 255)
				return (free(d->check_rgb_nb), free(d->check_rgb_number), 0);
			continue ;
		}
		else if ((color[d->rgbi] >= '0' && color[d->rgbi] <= '9'))
		{
			d->check_rgb_number = cj(d->check_rgb_number, color[d->rgbi], 0);
			if (!d->check_rgb_number)
				return (free(d->check_rgb_nb), free(d->check_rgb_number), 0);
		}
		else
			return (free(d->check_rgb_nb), free(d->check_rgb_number), 0);
	}
	return (check_rgb_end(d, param));
}

int	check_rgb_early(char *color, t_data *data, int param)
{
	data->rgbi = -1;
	data->rgbj = -1;
	data->check_rgb_nb = ft_calloc(sizeof(int), 3);
	if (!data->check_rgb_nb)
		return (0);
	data->check_rgb_number = 0;
	if (color[0] < '0' || color[0] > '9')
		return (free(data->check_rgb_nb), 0);
	return (free(data->check_rgb_number), check_rgb_fc(color, data, param));
}
