/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/12/04 17:40:29 by aproust          ###   ########.fr       */
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

int   draw(t_data *data, int x)
{
      double  perpwalldist;
      int     lineheight;
      int     drawEnd;
      int     k;
      int     pixel_index;
      double  wallx;
      int     texdir;

      (void)texdir;
      (void)pixel_index;
      if(data->side == 0)
        perpwalldist = (data->sideDistX - data->deltaDistX);
      else
        perpwalldist = (data->sideDistY - data->deltaDistY);

      lineheight = (int)(WIDTH / perpwalldist);
      data->drawstart = -lineheight / 2 + WIDTH / 2;
      if(data->drawstart < 0)
        data->drawstart = 0;
      drawEnd = lineheight / 2 + WIDTH / 2;
      if(drawEnd >= WIDTH)
        drawEnd = WIDTH - 1;

	    if (data->side == 0 && data->raydirx < 0)
	    	texdir = 0;
	    else if (data->side == 0 && data->raydirx >= 0)
	    	texdir = 1;
	    else if (data->side == 1 && data->raydiry < 0)
	    	texdir = 2;
	    else if (data->side == 1 && data->raydiry >= 0)
	    	texdir = 3;
	    if (data->side == 0)
	    	wallx = data->posy + perpwalldist * data->raydiry;
	    else
	    	wallx = data->posx + perpwalldist * data->raydirx;
	    wallx -= floor((wallx));
	    data->step = 1.0 * data->h / lineheight;
	    data->texx = (int)(wallx * (double)data->w);
	    if (data->side == 0 && data->raydirx > 0)
	    	data->texx = data->w - data->texx - 1;
	    else if (data->side == 1 && data->raydiry < 0)
	    	data->texx = data->w - data->texx - 1;
	    data->texpos = (data->drawstart - WIDTH / 2 + lineheight / 2) * data->step;
      k = -1;
      while (++k < data->drawstart)
      {
          // mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, data->cc);
          pixel_index = k * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
          data->win_addr[pixel_index] = (data->cc >> 16);
          data->win_addr[pixel_index + 1] = (data->cc >> 8);
          data->win_addr[pixel_index + 2] = data->cc;
      }
	    while (++k < drawEnd)
	    {
        // mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, 0xFF0000);
	    	data->texy = (int)data->texpos & (64 - 1);
	    	data->texpos += data->step;
	    	data->win_addr[k * data->line_bytes[0] + x * (data->pixel_bits[0] / 8)] =
  			data->addr[texdir][64 * data->texy + data->texx];
	    }
      while (++k < WIDTH)
      {
          // mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, data->cf);
          pixel_index = k * data->line_bytes[0] + x * (data->pixel_bits[0] / 8);
          data->win_addr[pixel_index] = (data->cf >> 16);
          data->win_addr[pixel_index + 1] = (data->cf >> 8);
          data->win_addr[pixel_index + 2] = data->cf;
      }
      mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
      // draw_minimap(data);
      return (1);
}

int	raytracing(t_data *data)
{
    int    x;
    double cameraX;
    int    mapX;
    int    mapY;
    int    stepX;
    int    stepY;
    int    hit;

    x = 0;
    while (x++ < HEIGHT)
    {
      cameraX = 2 * x / (double)HEIGHT - 1;
      data->raydirx = data->dirX + data->planeX * cameraX;
      data->raydiry = data->dirY + data->planeY * cameraX;
      mapY = (int)data->posy;
      mapX = (int)data->posx;
      data->deltaDistX = fabs(1 / data->raydirx);
      data->deltaDistY = fabs(1 / data->raydiry);
      hit = 0;
      if(data->raydirx < 0)
      {
        stepX = -1;
        data->sideDistX = (data->posx - mapX) * data->deltaDistX;
      }
      else
      {
        stepX = 1;
        data->sideDistX = (mapX + 1.0 - data->posx) * data->deltaDistX;
      }
      if(data->raydiry < 0)
      {
        stepY = -1;
        data->sideDistY = (data->posy - mapY) * data->deltaDistY;
      }
      else
      {
        stepY = 1;
        data->sideDistY = (mapY + 1.0 - data->posy) * data->deltaDistY;
      }
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(data->sideDistX < data->sideDistY)
        {
          data->sideDistX += data->deltaDistX;
          mapX += stepX;
          data->side = 0;
        }
        else
        {
          data->sideDistY += data->deltaDistY;
          mapY += stepY;
          data->side = 1;
        }
        //Check if ray has hit a wall
        if(data->map[mapX][mapY] == '1')
          hit = 1;
      }
      draw(data, x);
    }
    return (0);
}


        // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (k) * (data->pixel_bits[0] / 8)))  = data->cc;
        // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (l) * (data->pixel_bits[0] / 8))) = 0xFF0000;
        // *(int *)((data->win_addr + (x * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + (k) * (data->pixel_bits[0] / 8))) = data->cf;
      // printf("line_bytes:%d et pixel_bits:%d\n", data->line_bytes[0], data->pixel_bits[0]);
      // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window, 0, 0);
