/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:03:45 by slevaslo          #+#    #+#             */
/*   Updated: 2023/12/12 19:19:43 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_address(t_data *data)
{
	data->addr = (int **)ft_calloc(sizeof(int *), 5);
	data->addr[0] = (int *)mlx_get_data_addr(data->img[0],
			&data->pixel_bits[1], &data->line_bytes[1], &data->edian[1]);
	data->addr[1] = (int *)mlx_get_data_addr(data->img[1],
			&data->pixel_bits[2], &data->line_bytes[2], &data->edian[2]);
	data->addr[2] = (int *)mlx_get_data_addr(data->img[2],
			&data->pixel_bits[3], &data->line_bytes[3], &data->edian[3]);
	data->addr[3] = (int *)mlx_get_data_addr(data->img[3],
			&data->pixel_bits[4], &data->line_bytes[4], &data->edian[4]);
}

int	get_texture(t_data *data)
{
	data->img = ft_calloc(sizeof(void *), 5);
	data->img[0] = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[0],
			&data->w[0], &data->h[0]);
	if (!data->img[0])
		return (1);
	data->img[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->txtr[1], &data->w[1], &data->h[1]);
	if (!data->img[1])
		return (1);
	data->img[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->txtr[2], &data->w[2], &data->h[2]);
	if (!data->img[2])
		return (1);
	data->img[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			data->txtr[3], &data->w[3], &data->h[3]);
	if (!data->img[3])
		return (1);
	get_texture_address(data);
	return (0);
}

int	check_texture(t_data *data)
{
	int	fd[4];

	fd[0] = open(data->txtr[0], 0);
	if (fd[0] < 0)
		return (1);
	fd[1] = open(data->txtr[1], 0);
	if (fd[1] < 0)
		return (close(fd[0]), 1);
	fd[2] = open(data->txtr[2], 0);
	if (fd[2] < 0)
		return (close(fd[0]), close(fd[1]), 1);
	fd[3] = open(data->txtr[3], 0);
	if (fd[3] < 0)
		return (close(fd[0]), close(fd[1]), close(fd[2]), 1);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (0);
}
