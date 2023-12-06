/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:37 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/06 18:06:30 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_map(int fd)
{
	char	*buffer;
	char	*str;

	str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	buffer = get_next_line(fd);
	while (buffer)
	{
		str = ft_strjoin(str, buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	return (str);
}

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

	// int nb_of_dir = 0;
	int j = 0;
	while(data->file[i][j] == ' ')
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
	int	y = 0;
	while(data->file[i][y] == ' ')
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
	int	i;
	int	j;
	char	ch;
	int nbr_of_wall = 0;
	// int	nbr_of_floor = 0;
	i = -1;
	while (data->file[++i] && i <= 5)
	{
		j = -1;
		if (nbr_of_wall <= 4)
			ch = which_char(data, i);
		// if (ch == 'F')
		// 	return (1);
		if ((nbr_of_wall <= 4) && ((ch == 'N') || (ch == 'S') || (ch == 'W') || (ch == 'E')))
		{
			if (parse_for_texture(data, ch, i, j))
			{
				return (1);
			}
			nbr_of_wall++;
		}
		else if (get_floor_and_ceiling(data, i, j))
			return (1);
	}
	if (check_map(data, &data->file[i]))
		return (1);
	return (0);
}

int	map_fill(t_data *data, int fd)
{
	char	*str;

	str = get_map(fd);
	if (!str)
		return (1);
	if (parse_map(str))
		return (free(str), 1);
	data->file = ft_split(str, '\n');
	if (!data->file)
		return (1);
	if (parse_file(data))
	{
		close(fd);
		return (free(str), 1);
	}
	close(fd);
	free(str);
	return (0);
}

int	int_join(int *n)
{
	int i;
	i = n[0];
	i = i * 256;
	i = i + n[1];
	i = i * 256;
	i = i + n[2];
	return (i);
}

void	map_init(t_data *data, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 1)
		close_error("File does not exist\n", data);
	if (map_fill(data, fd))
		close_error("Map is wrong\n", data);
	data->cf = int_join(data->f_color);
	data->cc = int_join(data->c_color);
}
