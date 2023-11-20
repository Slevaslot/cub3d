/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sequel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:40:03 by aproust           #+#    #+#             */
/*   Updated: 2023/11/20 17:06:53 by aproust          ###   ########.fr       */
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

int	check_map(t_data *data, char **mp)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	j = -1;
	data->map = ft_calloc(sizeof(char *), tab_size(data->file));
	while (mp[++j])
	{
		data->map[j] = ft_strdup(mp[j]);
		i = -1;
		while (mp[j][++i])
		{
			if (mp[j][i] == '1' || mp[j][i] == ' ')
				;
			else if (z(mp[j][i]) && (mp[j][i - 1] && (mp[j][i - 1] == '1'
				|| z(mp[j][i - 1])) && (mp[j][i + 1]) && (mp[j][i + 1] == '1'
				|| z(mp[j][i + 1])) && (mp[j - 1][i]) && (mp[j - 1][i] == '1'
				|| z(mp[j - 1][i])) && (mp[j + 1][i]) && (mp[j + 1][i] == '1'
				|| z(mp[j + 1][i])) && (mp[j + 1][i + 1])
				&& (mp[j + 1][i + 1] == '1' || z(mp[j + 1][i + 1]))
				&& (mp[j - 1][i - 1]) && (mp[j - 1][i - 1] == '1'
				|| z(mp[j - 1][i - 1]))))
			{
				if (mp[j][i] != '1' && mp[j][i] != '0' && mp[j][i] != 'W'
					&& mp[j][i] != 'E' && mp[j][i] != 'N' && mp[j][i] != 'S'
					&& mp[j][i] != ' ')
					return (1);
				if (mp[j][i] == 'E' || mp[j][i] == 'N' || mp[j][i] == 'W'
					|| mp[j][i] == 'S')
					counter++;
			}
			else
				return (1);
		}
	}
	if (counter != 1)
		return (1);
	return (0);
}
