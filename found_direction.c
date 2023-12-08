/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:05:09 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/08 19:00:58 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	est_west_dir(t_data *data)
{
	if (data->player_dir == 'E')
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = 0.66;
		data->planey = 0;
	}
	else if (data->player_dir == 'W')
	{
		data->dirx = 0;
		data->diry = -1;
		data->planex = -0.66;
		data->planey = 0;
	}
}

void	found_player_dir(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = 0.66;
	}
	else if (data->player_dir == 'S')
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -0.66;
	}
	else
		est_west_dir(data);
}
