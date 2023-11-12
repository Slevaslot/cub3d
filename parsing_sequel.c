/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sequel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:40:03 by aproust           #+#    #+#             */
/*   Updated: 2023/11/12 16:36:36 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(char **map)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			// if ((map[j][i] == '0' && j != 0 && i != 0) && map[j][i])
			if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != 'W'
				&& map[j][i] != 'E' && map[j][i] != 'N' && map[j][i] != 'S'
				&& map[j][i] != ' ')
				return (1);
			if (map[j][i] == 'E' || map[j][i] == 'N'|| map[j][i] == 'W'
				|| map[j][i] == 'S')
				counter++;
		}
	}
	if (counter != 1)
	 	return (1);
	return (0);
}
