/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/12/08 15:25:40 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_minimap(t_data *data)
{
	float	x;
	float	y;
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
            int pixel_index = (int)((x * line_bytes / (pixel_bits / 8) * 10) + (y * 10));
			if ((int)x == (int)data->posx && (int)y == (int)data->posy)
				color = 0xFF0000;
			else if (data->map[(int)x][(int)y] == '0' || data->map[(int)x][(int)y] == 'N' || data->map[(int)x][(int)y] == 'S' || data->map[(int)x][(int)y] == 'E' || data->map[(int)x][(int)y] == 'W') // Mur
                color = data->cf;
            else if (data->map[(int)x][(int)y] == '1')
                color = 0x606060;
            else
                color = 0x000000;
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

   x = -1;
   while (++x < WIDTH)
   {
     cameraX = 2 * x / (double)WIDTH - 1;
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
       if(data->map[mapX][mapY] == '1')
         hit = 1;
     }
     double  perpwalldist;
     int     lineheight;
     int     drawEnd;
     int     y;
     double  wallx;
     int     texdir;
     int     pixel_index;

     (void)pixel_index;
     if(side == 0)
       perpwalldist = (mapX - data->posx + (1 - stepX) / 2) / raydirx;
     else
       perpwalldist = (mapY - data->posy + (1 - stepY) / 2) / raydiry;
     lineheight = (int)(HEIGHT / perpwalldist);
     data->drawstart = -lineheight / 2 + HEIGHT / 2;
     if(data->drawstart < 0)
       data->drawstart = 0;
     drawEnd = lineheight / 2 + HEIGHT / 2;
     if(drawEnd >= HEIGHT)
       drawEnd = HEIGHT - 1;
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
	   data->step = 1.0 * 64 / lineheight;
	   data->texx = (int)(wallx * (double)64);
	   if (side == 0 && raydirx > 0)
	   	data->texx = 64 - data->texx - 1;
	   if (side == 1 && raydiry < 0)
	   	data->texx = 64 - data->texx - 1;
	   data->texpos = (data->drawstart - HEIGHT / 2 + lineheight / 2) * data->step;
     y = -1;
     while (++y < data->drawstart)
     {
      pixel_index = y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
        data->win_addr[pixel_index] = (data->cc);
        data->win_addr[pixel_index + 1] = (data->cc >> 8);
        data->win_addr[pixel_index + 2] = (data->cc >> 16);
     }
	   while (++y < drawEnd)
	   {
	   	data->texy = (int)data->texpos & (64 - 1);
	   	data->texpos += data->step;
      int color;
      color = data->addr[texdir][64 * data->texy + data->texx];
      if (side == 1)
			  color = (color >> 1) & 8355711;
       ft_memcpy(&data->win_addr[y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)], &color, 4);
	   }
     y = drawEnd;
     while (++y < HEIGHT)
     {
      pixel_index = y * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
      data->win_addr[pixel_index] = data->cf;
      data->win_addr[pixel_index + 1] = (data->cf >> 8);
      data->win_addr[pixel_index + 2] = (data->cf >> 16);
     }
   }
   mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
   draw_minimap(data);
   return (1);
}
