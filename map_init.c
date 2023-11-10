/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:37 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/10 17:39:42 by aproust          ###   ########.fr       */
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
		while(data->map[i][++j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != 'N')
				return (1);
			if (data->map[i][j] == 'N')
			{
				if (data->map[i][++j] && data->map[i][j] == 'O')
					data->ntex = ft_strtrim(&map[i][++j], " ");
			}
		}
	}
	return (0);
}

int	map_fill(t_data *data, int fd)
{
	int		i;
	char	*str;

	i = 0;
	str = get_map(fd);
	data->map = ft_split(str, '\n');
	if (!data->map)
		return (1);
	if (check_map(data))
	{
		close(fd);
		return (free(str), 1);
	}
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
	// Mettre les textures et couleur dans Data
	if (map_fill(data, fd))
		close_error("Map is wrong\n", data);
}
