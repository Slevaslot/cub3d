/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:47:37 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 18:19:31 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cj(char *str, char c, int param)
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

int	get_floor_color(t_data *data, int i, int j)
{
	while (data->file[i][++j])
	{
		if (data->file[i][j] != ' ' && data->file[i][j] != 'F')
			return (1);
		if (data->file[i][j] == 'F')
		{
			if (data->file[i][++j] && data->file[i][j] == ' ')
				data->txtr[4] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	if (!check_rgb_early(data->txtr[4], data, 0))
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
				data->txtr[5] = ft_strtrim(&data->file[i][++j], " ");
			else
				return (1);
			break ;
		}
	}
	if (!check_rgb_early(data->txtr[5], data, 1))
		return (1);
	return (0);
}
