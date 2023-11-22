/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:10 by aproust           #+#    #+#             */
/*   Updated: 2023/11/22 18:22:54 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define screenWidth 1920
#define screenHeight 1080
#define mapWidth 24
#define mapHeight 24

int	raytracing(t_data *data)
{
  printf("posx:%f\n, posy:%f\n", data->posX, data->posY);
    for(int x = 0; x < 1920; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)1920 - 1; //x-coordinate in camera space
      double rayDirX = data->dirX + data->planeX * cameraX;
      double rayDirY = data->dirY + data->planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)data->posX;
      int mapY = (int)data->posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      // double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      // double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (data->posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (data->posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
      }
      //perform DDA
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
        if(data->map[mapX][mapY] == '1') hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - data->posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(1080 / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + 1080 / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + 1080 / 2;
      if(drawEnd >= 1080) drawEnd = 1080 - 1;

      //choose wall color
      // ColorRGB color;
      // switch(data->map[mapX][mapY])
      // {
      //   case 1:  color = RGB_Red;    break; //red
      //   case 2:  color = RGB_Green;  break; //green
      //   case 3:  color = RGB_Blue;   break; //blue
      //   case 4:  color = RGB_White;  break; //white
      //   default: color = RGB_Yellow; break; //yellow
      // }

      //give x and y sides different brightness
      // if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      int l = -1;
      int k = -1;
      // printf("%d\n", drawStart);
      while (++k < drawStart)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, data->cc);
      while (drawStart + ++l < drawEnd)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, drawStart + l, 0xFF0000);
      k = drawEnd;
      while (++k < 1080)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, k, data->cf);
      // verLine(x, drawStart, drawEnd, color);
    }
    return (1);
}