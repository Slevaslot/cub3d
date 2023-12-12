/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:05 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 17:07:48 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_for_texture3(t_data *data, int i, int j)
{
	while (data->file[i][++j])
	{
		if (data->file[i][j] != ' ' && data->file[i][j] != 'E')
			return (1);
		if (data->file[i][j] == 'E')
		{
			if (data->file[i][++j] && data->file[i][j] == 'A'
			&& data->file[i][j + 1] == ' ')
				data->txtr[3] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	parse_for_texture2(t_data *data, int i, int j)
{
	while (data->file[i][++j])
	{
		if (data->file[i][j] != ' ' && data->file[i][j] != 'W')
		{
			return (1);
		}
		if (data->file[i][j] == 'W')
		{
			if (data->file[i][++j] && data->file[i][j] == 'E'
			&& data->file[i][j + 1] == ' ')
				data->txtr[2] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	parse_for_texture_est_west(t_data *data, char c, int i, int j)
{
	if (c == 'W')
	{
		if (parse_for_texture2(data, i, j))
		{
			return (1);
		}
	}
	else if (c == 'E')
	{
		if (parse_for_texture3(data, i, j))
			return (1);
	}
	return (0);
}

int	parse_for_texture(t_data *data, char c, int i, int j)
{
	if (c == 'N' || c == 'S')
	{
		while (data->file[i][++j])
		{
			if (data->file[i][j] != ' ' && data->file[i][j] != c)
				return (1);
			if (data->file[i][j] == c)
			{
				if (data->file[i][++j] && data->file[i][j] == 'O'
				&& data->file[i][j + 1] == ' ' && c == 'N')
					data->txtr[0] = ft_strtrim(&data->file[i][++j], " ");
				else if (data->file[i][j] && data->file[i][j] == 'O'
				&& data->file[i][j + 1] == ' ' && c == 'S')
					data->txtr[1] = ft_strtrim(&data->file[i][++j], " ");
				else
					return (1);
				break ;
			}
		}
	}
	if (parse_for_texture_est_west(data, c, i, j) == 1)
		return (1);
	return (0);
}
