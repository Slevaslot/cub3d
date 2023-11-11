/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:37 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/11 17:49:35 by aproust          ###   ########.fr       */
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

int	check_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		if (i == 0)
		{
			if (parse_for_texture(data, 'N', i, j))
				return (1);
		}
		else if (i == 1)
		{
			if (parse_for_texture(data, 'S', i, j))
				return (1);
		}
		else if (i == 2)
		{
			if (parse_for_texture(data, 'W', i, j))
				return (1);
		}
		else if (i == 3)
		{
			if (parse_for_texture(data, 'E', i, j))
				return (1);
		}
		else if (i == 4)
		{
			if (get_floor_color(data, i, j))
				return (1);
		}
		else if (i == 5)
		{
			if (get_ceiling_color(data, i, j))
				return (1);
		}
	}
	return (0);
}

int	map_fill(t_data *data, int fd)
{
	char	*str;

	str = get_map(fd);
	data->map = ft_split(str, '\n');
	if (!data->map)
		return (1);
	if (check_map(data))
	{
		close(fd);
		return (free(str), 1);
	}
	int i = -1;
	while (++i < 6)
		printf("check: |%s|\n", data->textures[i]);
	close(fd);
	free(str);
	return (0);
}

void	map_init(t_data *data, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 1)
		close_error("File does not exist\n", data);
	if (map_fill(data, fd))
		close_error("Map is wrong\n", data);
}
