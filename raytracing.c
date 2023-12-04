/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/12/04 17:37:55 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raytracing(t_data *data)
{
    int    x;
    double cameraX;
    double rayDirX;
    int    mapY;
    int    mapX;
    double rayDirY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int    stepX;
    int    stepY;
    int    hit;
    int    side;

    x = 0;
    while (x++ < HEIGHT)
    {
      cameraX = 2 * x / (double)HEIGHT - 1;
      rayDirX = data->dirX + data->planeX * cameraX;
      rayDirY = data->dirY + data->planeY * cameraX;
      mapY = (int)data->posy;
      mapX = (int)data->posx;
      deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      hit = 0;
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (data->posx - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->posx) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (data->posy - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->posy) * deltaDistY;
      }
      while (hit == 0)
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
      //This can be computed as (mapX - data->posx + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0)
        perpWallDist = (sideDistX - deltaDistX);
      else
        perpWallDist = (sideDistY - deltaDistY);

      int lineHeight;
      int drawStart;
      int drawEnd;
      int l;
      int k;
      int i;
      int pixel_value;

      lineHeight = (int)(WIDTH / perpWallDist);
      drawStart = -lineHeight / 2 + WIDTH / 2;
      if(drawStart < 0)
        drawStart = 0;
      drawEnd = lineHeight / 2 + WIDTH / 2;
      if(drawEnd >= WIDTH)
        drawEnd = WIDTH - 1;
      l = -1;
      k = -1;
      while (++k < drawStart)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, data->cc);
        // (int)((data->window + k * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + x) = data->cc;
      while (drawStart + ++l < drawEnd)
      {
        if (l >= (drawEnd - drawStart) - ((drawEnd - drawStart) * (((16 - i)/ 16))))
          i++;
        pixel_value = *(int *)(data->addr[0] + i);
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart + l, pixel_value);
      }
      k = drawEnd;
      while (++k < WIDTH)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, data->cf);
        // (int)((data->window + k * data->line_bytes[0] / (data->pixel_bits[0] / 8)) + x) = data->cf;
      // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img[0])
      // draw_minimap(data);
    }
    return (1);
}
