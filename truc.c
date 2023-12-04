/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:16:04 by aproust           #+#    #+#             */
/*   Updated: 2023/12/04 17:34:22 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
// mlx_hook(recup->data.mlx_win, 2, 1L << 0, ft_key_press, recup);
// mlx_hook(recup->data.mlx_win, 3, 1L << 1, ft_key_release, recup);

void	draw_minimap_bis(t_data *data)
{
	float		x;
	float		y;

	y = 0;
	while (data->map[(int)y] != NULL)
	{
		x = 0;
		while (data->map[(int)y][(int)x] != '\0')
		{
			if (data->map[(int)y][(int)x] == '0') // Mur
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0xFFFFFF); // Blanc
			else if (data->map[(int)y][(int)x] == 'N' || data->map[(int)y][(int)x] == 'S' || data->map[(int)y][(int)x] == 'E' || data->map[(int)y][(int)x] == 'W') // Joueur
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0xFF0000); // Rouge
			else if (data->map[(int)y][(int)x] == '1') // Objet
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0x00FF00); // Vert
			else
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 20, y * 20, 0x000000); // Noir (espace vide)
			x += 0.1;
		}
		y += 0.1;
	}
}

void	draw_minimap_trois(t_data *data)
{
	float		x;
	float		y;
	int	pixel_bits;
	int	line_bytes;
	int	edian;
	int color;
	float ok;

	ok = 32;
	y = 0;
	data->addrformini = mlx_get_data_addr(data->image_mini, &pixel_bits, &line_bytes, &edian);
while (data->map[(int)y] != NULL)
{
    x = 0;
    while (data->map[(int)y][(int)x] != '\0')
    {
        if (data->map[(int)y][(int)x] == '1') // Mur
            color =  0xFFFFFF; // Blanc
        else if (x == data->posx && y == data->posy) // Joueur
            color = 0xFF0000; // Rouge
        else if (data->map[(int)y][(int)x] == '0') // Objet
            color = 0x00FF00; // Vert
        else
            color = 0x000000; // Noir (espace vide)

        // Calcul de l'index en prenant en compte la position de la ligne dans la minimap
        int index = (int)(y * ok + x * (ok / 8));

        // Ajout de la position en y pour obtenir un retour à la ligne
        int yOffset = (int)(y * ok);

        // Modification de la position mémoire
        *(unsigned int *)(data->addrformini + index + yOffset) = color;
        x += 1;
    }
    y += 1;
}
	// while (y < 50) // Changer la taille de la fenêtre selon vos besoins
	// {
	// 	x = 0;
	// 	while (x < 50) // Changer la taille de la fenêtre selon vos besoins
	// 	{
	// 		// Exemple de couleur : violet (mix de rouge et de bleu)
	// 		color = 0x00FF00FF;
	// 		// Remplacez le pixel à la position (x, y) par la nouvelle couleur
	// 		*(unsigned int *)(data->addrformini + ((int)(y * ok + x * (ok / 8)))) = color;
	// 		x++;
	// 	}
	// 	y++;
	// }
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image_mini, 0, 0);
	// 	}
	// 	y += 0.1;
	// }
}
void	rotate_left(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->map[++j])
	{
		while (data->map[j][++i])
		{
			if (data->map[j][i] == 'N')
			{
				data->map[j][i] = 'W';
				return ;
			}
			if (data->map[j][i] == 'W')
			{
				data->map[j][i] = 'S';
				return ;
			}
			if (data->map[j][i] == 'S')
			{
				data->map[j][i] = 'E';
				return ;
			}
			if (data->map[j][i] == 'E')
			{
				data->map[j][i] = 'N';
				return ;
			}
		}
		i = -1;
	}
}

void	rotate_right(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->map[++j])
	{
		while (data->map[j][++i])
		{
			if (data->map[j][i] == 'N')
			{
				data->map[j][i] = 'E';
				return ;
			}
			if (data->map[j][i] == 'E')
			{
				data->map[j][i] = 'S';
				return ;
			}
			if (data->map[j][i] == 'S')
			{
				data->map[j][i] = 'W';
				return ;
			}
			if (data->map[j][i] == 'W')
			{
				data->map[j][i] = 'N';
				return ;
			}
		}
		i = -1;
	}
}

void	image_error(t_data *data, int j)
{
	while (j > 0)
		mlx_destroy_image(data->mlx_ptr, data->img2[--j]);
	data->err = 1;
	exit(0);
}

void	put_image(t_data *data, int *j, char *str)
{
	int		h;
	int		w;

	h = 64;
	w = 64;
	data->img2[j[2]] = mlx_xpm_file_to_image(data->mlx_ptr, str, &w, &h);
	if (!data->img2[j[2]])
		image_error(data, j[2]);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img2[j[2]], j[0], j[1]);
}

void	browse_char(t_data *data, char c, int *j)
{
	if (c == '0')
		put_image(data, j, "img/0.xpm");
	else if (c == '1')
		put_image(data, j, "img/1.xpm");
	else if (c == 'N')
		put_image(data, j, "img/N.xpm");
	else if (c == 'S')
		put_image(data, j, "img/S.xpm");
	else if (c == 'E')
		put_image(data, j, "img/E.xpm");
	else if (c == 'W')
		put_image(data, j, "img/W.xpm");
}

int	alloc_img(t_data *data)
{
	data->img2 = malloc(sizeof(void *) * WIDTH);
	if (!data->img2)
		return (1);
	return (0);
}

void	browse_image(t_data *data)
{
	int	i[2];
	int	j[3];

	j[0] = 0;
	j[1] = 0;
	j[2] = -1;
	i[0] = -1;
	if (alloc_img(data))
		return ;
	while (data->map[++i[0]])
	{
		i[1] = -1;
		while (data->map[i[0]][++i[1]])
		{
			++j[2];
			browse_char(data, data->map[i[0]][i[1]], j);
			j[0] += 64;
		}
		j[1] += 64;
		j[0] = 0;
	}
}
