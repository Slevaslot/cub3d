/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:05 by aproust           #+#    #+#             */
/*   Updated: 2023/11/20 18:11:01 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*charjoin(char *str, char c, int param)
{
	int		i;
	char	*nstr;

	i = 0;
	nstr = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!nstr)
		return (NULL);
	while (str && str[i])
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = c;
	nstr[i + 1] = '\0';
	if (param == 0)
		free(str);
	return (nstr);
}

int	check_rgb_fc(char *color, t_data *data, int param)
{
	int		i;
	char	*number;
	int		j;
	int		*nbr;

	i = -1;
	j = -1;
	nbr = ft_calloc(sizeof(int), 3);
	number = 0;
	if (color[0] < '0' || color[0] > '9')
		return (0);
	while (color[++i] && j != 2)
	{
		if (color[i] == ' ')
			continue ;
		else if (color[i] == ',')
		{
			nbr[++j] = ft_atoi(number);
			free(number);
			number = ft_calloc(sizeof(char), 1);
			if (nbr[j] < 0 || nbr[j] > 255)
				return (free(number), 0);
			continue ;
		}
		else if ((color[i] >= '0' && color[i] <= '9'))
		{
			number = charjoin(number, color[i], 0);
			if (!number)
				return (free(number), 0);
		}
		else
			return (0);
	}
	nbr[++j] = ft_atoi(number);
	free(number);
	if (j != 2)
		return (0);
	if (param == 0)
		data->f_color = nbr;
	else if (param == 1)
		data->c_color = nbr;
	return (1);
}

int	get_floor_color(t_data *data, int i, int j)
{
	while (data->file[i][++j])
	{
		if (data->file[i][j] != ' ' && data->file[i][j] != 'F')
			return (1);
		if (data->file[i][j] == 'F')
		{
			if (data->file[i][++j] && data->file[i][j] == ' ')
				data->textures[4] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	if (!check_rgb_fc(data->textures[4], data, 0))
		return (1);
	return (0);
}

int	get_ceiling_color(t_data *data, int i, int j)
{
	while (data->file[i][++j])
	{
		if (data->file[i][j] != ' ' && data->file[i][j] != 'C')
			return (1);
		if (data->file[i][j] == 'C')
		{
			if (data->file[i][++j] && data->file[i][j] == ' ')
				data->textures[5] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	if (!check_rgb_fc(data->textures[5], data, 1))
		return (1);
	return (0);
}

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
				data->textures[3] = ft_strtrim(&data->file[i][++j], " ");
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
			return (1);
		if (data->file[i][j] == 'W')
		{
			if (data->file[i][++j] && data->file[i][j] == 'E'
			&& data->file[i][j + 1] == ' ')
				data->textures[2] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	return (0);
}

int	parse_for_texture(t_data *data, char c, int i, int j)
{
	char	c2;

	if (c == 'N' || c == 'S')
	{
		c2 = 'O';
		while (data->file[i][++j])
		{
			if (data->file[i][j] != ' ' && data->file[i][j] != c)
				return (1);
			if (data->file[i][j] == c)
			{
				if (data->file[i][++j] && data->file[i][j] == c2
				&& data->file[i][j + 1] == ' ' && c == 'N')
					data->textures[0] = ft_strtrim(&data->file[i][++j], " ");
				else if (data->file[i][j] && data->file[i][j] == c2
				&& data->file[i][j + 1] == ' ' && c == 'S')
					data->textures[1] = ft_strtrim(&data->file[i][++j], " ");
				else
					return (1);
				break ;
			}
		}
	}
	else if (c == 'W')
	{
		if (parse_for_texture2(data, i, j))
			return (1);
	}
	else if (c == 'E')
	{
		if (parse_for_texture3(data, i, j))
			return (1);
	}
	return (0);
}
