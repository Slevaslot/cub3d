/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/12/03 17:17:20 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    int    x;
    double cameraX;
    double raydirx;
    int    mapY;
    int    mapX;
    double raydiry;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    int    stepX;
    int    stepY;
    int    hit;
    int    side;

    x = 0;
    while (x++ < 1920)
    {
      cameraX = 2 * x / (double)1920 - 1;
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
      int     k;
      int     y;
      int     pixel_index;
      double  wallx;
      int     texdir;

      if(side == 0)
        perpwalldist = (sideDistX - deltaDistX);
      else
        perpwalldist = (sideDistY - deltaDistY);

      lineheight = (int)(1016 / perpwalldist);
      data->drawstart = -lineheight / 2 + 1016 / 2;
      if(data->drawstart < 0)
        data->drawstart = 0;
      drawEnd = lineheight / 2 + 1016 / 2;
      if(drawEnd >= 1016)
        drawEnd = 1016 - 1;

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
	    wallx -= floor((wallx));
      y = data->drawstart - 1;
	    data->step = 1.0 * data->h / lineheight;
	    data->texx = (int)(wallx * (double)data->w);
	    if (side == 0 && raydirx > 0)
	    	data->texx = data->w - data->texx - 1;
	    if (side == 1 && raydiry < 0)
	    	data->texx = data->w - data->texx - 1;
      // dprintf(2, "texdir%d texx%d\n", texdir, data->texx);
	    data->texpos = (data->drawstart - 1016 / 2 + lineheight / 2) * data->step;
      k = -1;
      while (++k < data->drawstart)
      {
        printf("%d ", k);
          pixel_index = k * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
          data->win_addr[pixel_index] = (data->cc >> 16);
          data->win_addr[pixel_index + 1] = (data->cc >> 8);
          data->win_addr[pixel_index + 2] = data->cc;
      }
	    while (++y <= drawEnd)
	    {
        printf("%d ", y);
	    	data->texy = (int)data->texpos & (64 - 1);
	    	data->texpos += data->step;
	    	data->win_addr[y * data->line_bytes[texdir] + x * (data->pixel_bits[0] / 8)] =
	    			data->addr[texdir][64 * data->texy + data->texx];
	    }
      k = drawEnd;
      while (++k < 1016)
      {
        printf("%d ", k);
          pixel_index = k * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
          data->win_addr[pixel_index] = (data->cf >> 16);
          data->win_addr[pixel_index + 1] = (data->cf >> 8);
          data->win_addr[pixel_index + 2] = data->cf;
      }
      }
      mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
      // draw_minimap(data);
      return (1);
}

        // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (k) * (data->pixel_bits[0] / 8)))  = data->cc;
        // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (l) * (data->pixel_bits[0] / 8))) = 0xFF0000;
        // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (k) * (data->pixel_bits[0] / 8))) = data->cf;
      // printf("line_bytes:%d et pixel_bits:%d\n", data->line_bytes[0], data->pixel_bits[0]);
      // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
