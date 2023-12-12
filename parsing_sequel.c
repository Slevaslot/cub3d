/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sequel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:40:03 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 19:16:19 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	z(char c)
{
	if (c == '0' || c == 'W' || c == 'E' || c == 'N' || c == 'S')
		return (1);
	else
		return (0);
}

int	check_wall(char **mp, int i, int j)
{
	if (j == 0 || j == tab_size(mp) - 1 || i == 0 || i == (int)ft_strlen(mp[j]))
		return (0);
	else if (z(mp[j][i]) && (mp[j][i - 1] && (mp[j][i - 1] == '1'
				|| z(mp[j][i - 1])) && (mp[j][i + 1]) && (mp[j][i + 1] == '1'
				|| z(mp[j][i + 1])) && (mp[j - 1][i]) && (mp[j - 1][i] == '1'
				|| z(mp[j - 1][i])) && (mp[j + 1][i]) && (mp[j + 1][i] == '1'
				|| z(mp[j + 1][i]))))
		return (1);
	else
		return (0);
}

int	check_player(char **mp, int i, int j)
{
	if (mp[j][i] != '1' && mp[j][i] != '0' && mp[j][i] != 'W'
					&& mp[j][i] != 'E' && mp[j][i] != 'N' && mp[j][i] != 'S'
					&& mp[j][i] != ' ')
		return (1);
	return (0);
}

int	check_map_sequel(t_data *data, char **mp, int i, int j)
{
	if (mp[j][i] == '1' || mp[j][i] == ' ')
		;
	else if (check_wall(mp, i, j) == 1)
	{
		if (check_player(mp, i, j) == 1)
			return (1);
		if (mp[j][i] == 'E' || mp[j][i] == 'N' || mp[j][i] == 'W'
			|| mp[j][i] == 'S')
		{
			data->player_dir = mp[j][i];
			data->posx = j + 0.5;
			data->posy = i + 0.5;
			data->counter++;
		}
	}
	else
		return (1);
	return (0);
}

int	check_map(t_data *data, char **mp)
{
	int	i;
	int	j;
	int	length;

	length = -1;
	j = -1;
	data->counter = 0;
	data->map = ft_calloc(sizeof(char *), tab_size(mp) + 1);
	length = find_longest_line(mp);
	while (mp[++j])
	{
		data->map[j] = ft_strdup(mp[j]);
		i = ft_strlen(data->map[j]);
		while (++i < length + 1)
			mp[j] = cj(mp[j], ' ', 0);
		i = -1;
		while (mp[j][++i])
		{
			if (check_map_sequel(data, mp, i, j))
				return (1);
		}
	}
	if (data->counter != 1)
		return (1);
	return (0);
}
