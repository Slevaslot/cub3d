/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:05:09 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/08 17:11:53 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	est_west_dir(t_data *data)
{
	if (data->player_dir == 'E')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (data->player_dir == 'W')
	{
		data->dirX = 0;
		data->dirY = -1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
}

void	found_player_dir(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	else if (data->player_dir == 'S')
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
	else
		est_west_dir(data);
}
