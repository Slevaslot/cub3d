/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:37 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/08 18:18:04 by slevaslo         ###   ########.fr       */
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

int	find_longest_line(char **map)
{
	int	i;
	int	j;
	int	length;

	i = -1;
	length = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (length < j)
				length++;
		}
	}
	return (length);
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
	int	i;

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
