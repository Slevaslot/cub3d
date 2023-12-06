/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/12/06 20:40:13 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
  int	set_rgb(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	draw(t_data *data)
{
  int x;
  int y;

  x = 0;
  while (x++ < HEIGHT)
	{
	  y = 0;
		while (y++ < WIDTH)
			data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)] = data->buff[x][y];
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
}

void draw_minimap(t_data *data)
{
	float		x;
	float		y;
	int	pixel_bits;
	int	line_bytes;
	int	edian;
	int color;
	x = 0;
	data->addrformini = mlx_get_data_addr(data->image_mini, &pixel_bits, &line_bytes, &edian);
    while (data->map[(int)x] != NULL)
    {
        y = 0;
        while (data->map[(int)x][(int)y] != '\0')
        {
            int pixel_index = (int)((x * line_bytes / (pixel_bits / 8) * 10) + (y * 10)); // Calcul de l'index du pixel
			if ((int)x == (int)data->posx && (int)y == (int)data->posy)
				color = 0xFF0000;
			else if (data->map[(int)x][(int)y] == '0' || data->map[(int)x][(int)y] == 'N' || data->map[(int)x][(int)y] == 'S' || data->map[(int)x][(int)y] == 'E' || data->map[(int)x][(int)y] == 'W') // Mur
                color = data->cf;
            else if (data->map[(int)x][(int)y] == '1') // Objet
                color = 0x606060;
            else
                color = 0x000000; // Noir (espace vide)

            // Écriture directe dans la mémoire tampon
            *(unsigned int *)(data->addrformini + pixel_index * (pixel_bits / 8)) = color;
            y += 0.1;
        }
        x += 0.1;
    }
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image_mini, 0, 0);
}

int	raytracing(t_data *data)
{
   int     x;
   double  cameraX;
   double  raydirx;
   int     mapY;
   int     mapX;
   double  raydiry;
   double  sideDistX;
   double  sideDistY;
   double  deltaDistX;
   double  deltaDistY;
   int     stepX;
   int     stepY;
   int     hit;
   int     side;

  int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
  {
  	j = -1;
		while (++j < WIDTH)
			data->buff[i][j] = 0;
  }
   x = 0;
   while (x++ < HEIGHT)
   {
     cameraX = 2 * x / (double)HEIGHT - 1;
     raydirx = data->dirX + data->planeX * cameraX;
     raydiry = data->dirY + data->planeY * cameraX;
     mapY = (int)data->posy;
     mapX = (int)data->posx;
     deltaDistX = fabs(1 / raydirx);
     deltaDistY = fabs(1 / raydiry);
     hit = 0;
     if(raydirx < 0)
     {
       stepX = -1;
       sideDistX = (data->posx - mapX) * deltaDistX;
     }
     else
     {
       stepX = 1;
       sideDistX = (mapX + 1.0 - data->posx) * deltaDistX;
     }
     if(raydiry < 0)
     {
       stepY = -1;
       sideDistY = (data->posy - mapY) * deltaDistY;
     }
     else
     {
       stepY = 1;
       sideDistY = (mapY + 1.0 - data->posy) * deltaDistY;
     }
     while(hit == 0)
     {
       //jump to next map square, either in x-direction, or in y-direction
       if(sideDistX < sideDistY)
       {
         sideDistX += deltaDistX;
         mapX += stepX;
         side = 0;
       }
       else
       {
         sideDistY += deltaDistY;
         mapY += stepY;
         side = 1;
       }
       //Check if ray has hit a wall
       if(data->map[mapX][mapY] == '1')
         hit = 1;
     }
     //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
     //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
     //This can be computed as (mapX - data->posx + (1 - stepX) / 2) / raydirx for side == 0, or same formula with Y
     //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
     //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
     //steps, but we subtract deltaDist once because one step more into the wall was taken above.
     double  perpwalldist;
     int     lineheight;
     int     drawEnd;
     int     y;
     double  wallx;
     int     texdir;
     int     pixel_index;
     if(side == 0)
       perpwalldist = (mapX - data->posx + (1 - stepX) / 2) / raydirx;
     else
       perpwalldist = (mapY - data->posy + (1 - stepY) / 2) / raydiry;
     lineheight = (int)(WIDTH / perpwalldist);
     data->drawstart = -lineheight / 2 + WIDTH / 2;
     if(data->drawstart < 0)
       data->drawstart = 0;
     drawEnd = lineheight / 2 + WIDTH / 2;
     if(drawEnd >= WIDTH)
       drawEnd = WIDTH - 1;
     if (side == 0 && raydirx < 0)
	   	texdir = 0;
	   else if (side == 0 && raydirx >= 0)
	   	texdir = 1;
	   else if (side == 1 && raydiry < 0)
	   	texdir = 2;
	   else if (side == 1 && raydiry >= 0)
	   	texdir = 3;
     if (side == 0)
	   	wallx = data->posy + perpwalldist * raydiry;
	   else
	   	wallx = data->posx + perpwalldist * raydirx;
	   wallx -= floor(wallx);
	   data->step = 1.0 * data->h / lineheight;
	   data->texx = (int)(wallx * (double)data->w);
	   if (side == 0 && raydirx > 0)
	   	data->texx = data->w - data->texx - 1;
	   if (side == 1 && raydiry < 0)
	   	data->texx = data->w - data->texx - 1;
	   data->texpos = (data->drawstart - WIDTH / 2 + lineheight / 2) * data->step;
     y = -1;
     while (++y < data->drawstart)
     {
        // pixel_index = y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
        // data->win_addr[pixel_index] = (data->cc >> 16);
        // data->win_addr[pixel_index + 1] = (data->cc >> 8);
        // data->win_addr[pixel_index + 2] = data->cc;

      pixel_index = set_rgb(data->c_color);
      ft_memcpy(&data->buff[x][y], &pixel_index, 4);
        // data->buff[x][y] = set_rgb(data->c_color);
        // data->buff[x][y + 1] = (data->cf >> 8);
        // data->buff[x][y + 2] = data->cf;
        // data->buff[x][y] = data->cf >> 16 | data->cf >> 8 | data->cf;
     }
	   while (++y < drawEnd)
	   {
	   	data->texy = (int)data->texpos & (data->h - 1);
	   	data->texpos += data->step;
      ft_memcpy(&data->buff[x][y], &data->addr[texdir][data->h * data->texy + data->texx], 4);
      // data->buff[x][y] = data->addr[texdir][data->h * data->texy + data->texx];
      //  ft_memcpy(&data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)], &data->addr[texdir][data->h * data->texy + data->texx], 4);
	   	// data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)] =
	   	// 		data->addr[texdir][data->h * data->texy + data->texx];
	   }
     y = drawEnd;
     while (++y < WIDTH)
     {
      pixel_index = set_rgb(data->f_color);
        // data->buff[x][y] = set_rgb(data->f_color);
      ft_memcpy(&data->buff[x][y], &pixel_index, 4);
      // pixel_index = y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
      // data->win_addr[pixel_index] = (data->cf >> 16);
      // data->win_addr[pixel_index + 1] = (data->cf >> 8);
      // data->win_addr[pixel_index + 2] = data->cf;
        // data->buff[x][y] = (data->cf >> 16);
        // data->buff[x][y+ 1] = (data->cf >> 8);
        // data->buff[x][y + 2] = data->cf;
        // data->buff[x][y] = data->cf << 16 | data->cf << 8 | data->cf;
     }
   }
	  // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image_mini, 0, 0);
   draw(data);
   draw_minimap(data);
   return (1);
}
      // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (y) * (data->pixel_bits[0] / 8)))  = data->cc;
       // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (l) * (data->pixel_bits[0] / 8))) = 0xFF0000;
       // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (y) * (data->pixel_bits[0] / 8))) = data->cf;
     // printf("line_bytes:%d et pixel_bits:%d\n", data->line_bytes[0], data->pixel_bits[0]);
     // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
