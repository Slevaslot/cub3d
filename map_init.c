/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:35:37 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/08 19:48:17 by slevaslo         ###   ########.fr       */
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

int	map_fill(t_data *data, int fd)
{
	int		i;
	char	*str;

	i = 0;
	str = get_map(fd);
	while (str[++i])
	{
		if (str[0] == '\n' || (str[i] == '\n' && str[i - 1] == '\n'))
		{
			close(fd);
			return (free(str), 1);
		}
	}
	data->map = ft_split(str, '\n');
	close(fd);
	free(str);
	if (!data->map)
		return (free(data->map), 1);
	return (0);
}

void	map_init(t_data *data, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	// Check le nom de la map et si elle existe
	// Mettre les textures et couleur dans Data
	if (map_fill(data, fd))
		close_error(1);
}
