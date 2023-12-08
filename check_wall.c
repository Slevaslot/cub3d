/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:19:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/08 16:19:03 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(char *str)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (check == 1 && str[i] == '\n')
			return (1);
		while (str[i++] && str[i] != '\n')
		{
			if (str[i] != '0' && str[i] != '1' && str[i] != 'W' && str[i] != 'N'
				&& str[i] != 'S' && str[i] != 'E' && str[i] != ' ')
			{
				while (str[++i] && str[i] != '\n')
					;
				check = 0;
				break ;
			}
			else
				check = 1;
		}
	}
	return (0);
}

char	which_char(t_data *data, int i)
{
	int		j;

	j = 0;
	while (data->file[i][j] == ' ')
		j++;
	if (data->file[i][j] == 'N')
		return ('N');
	else if (data->file[i][j] == 'S')
		return ('S');
	else if (data->file[i][j] == 'W')
		return ('W');
	else if (data->file[i][j] == 'E')
		return ('E');
	else
		return ('F');
}

int	get_floor_and_ceiling(t_data *data, int i, int j)
{
	int		y;

	y = 0;
	while (data->file[i][y] == ' ')
		y++;
	if (data->file[i][y] == 'F')
	{
		if (get_floor_color(data, i, j))
			return (1);
	}
	else if (data->file[i][y] == 'C')
	{
		if (get_ceiling_color(data, i, j))
			return (1);
	}
	else
		return (1);
	y = 0;
	return (0);
}

int	parse_file(t_data *data)
{
	int		i;
	int		j;
	char	ch;
	int		nbr_of_wall;

	nbr_of_wall = 0;
	i = -1;
	while (data->file[++i] && i <= 5)
	{
		j = -1;
		if (nbr_of_wall <= 4)
			ch = which_char(data, i);
		if ((nbr_of_wall <= 4) && ((ch == 'N') || (ch == 'S')
				|| (ch == 'W') || (ch == 'E')))
		{
			if (parse_for_texture(data, ch, i, j))
				return (1);
			nbr_of_wall++;
		}
		else if (get_floor_and_ceiling(data, i, j))
			return (1);
	}
	if (check_map(data, &data->file[i]))
		return (1);
	return (0);
}
