/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:05 by aproust           #+#    #+#             */
/*   Updated: 2023/11/11 17:40:04 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_floor_color(t_data *data, int i, int j)
{
	while(data->map[i][++j])
	{
		if (data->map[i][j] != ' ' && data->map[i][j] != 'F')
			return (1);
		if (data->map[i][j] == 'F')
		{
			if (data->map[i][++j] && data->map[i][j] == ' ')
				data->textures[4] = ft_strtrim(&data->map[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	get_ceiling_color(t_data *data, int i, int j)
{
	while(data->map[i][++j])
	{
		if (data->map[i][j] != ' ' && data->map[i][j] != 'C')
			return (1);
		if (data->map[i][j] == 'C')
		{
			if (data->map[i][++j] && data->map[i][j] == ' ')
				data->textures[5] = ft_strtrim(&data->map[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	parse_for_texture3(t_data *data, int i, int j)
{
	while(data->map[i][++j])
	{
		if (data->map[i][j] != ' ' && data->map[i][j] != 'E')
			return (1);
		if (data->map[i][j] == 'E')
		{
			if (data->map[i][++j] && data->map[i][j] == 'A'
			&& data->map[i][j + 1] == ' ')
				data->textures[3] = ft_strtrim(&data->map[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	parse_for_texture2(t_data *data, int i, int j)
{
	while(data->map[i][++j])
	{
		if (data->map[i][j] != ' ' && data->map[i][j] != 'W')
			return (1);
		if (data->map[i][j] == 'W')
		{
			if (data->map[i][++j] && data->map[i][j] == 'E'
			&& data->map[i][j + 1] == ' ')
				data->textures[2] = ft_strtrim(&data->map[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	parse_for_texture(t_data *data, char c, int i, int j)
{
	char c2;

	if (c == 'N' || c == 'S')
	{
		c2 = 'O';
		while(data->map[i][++j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != c)
				return (1);
			if (data->map[i][j] == c)
			{
				if (data->map[i][++j] && data->map[i][j] == c2
				&& data->map[i][j + 1] == ' ' && c == 'N')
					data->textures[0] = ft_strtrim(&data->map[i][++j], " ");
				else if (data->map[i][j] && data->map[i][j] == c2
				&& data->map[i][j + 1] == ' ' && c == 'S')
					data->textures[1] = ft_strtrim(&data->map[i][++j], " ");
				else
					return (1);
				break ;
			}
		}
	}
	else if (c == 'W')
	{
		if (parse_for_texture2(data, i, j))
			return (1);
	}
	else if (c == 'E')
	{
		if (parse_for_texture3(data, i, j))
			return (1);
	}
	return (0);
}
