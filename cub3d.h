/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:03:42 by aproust           #+#    #+#             */
/*   Updated: 2023/12/12 15:51:17 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "libft_gnl/libft_gnl.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 2560
# define HEIGHT 1486

typedef struct t_data
{
	int		i;
	void	*mlx_ptr;
	void	*win_ptr;
	void	**img;
	char	**file;
	char	**map;
	char	**img2;
	char	**txtr;
	int		line_legth;
	char	*map_line;
	int		err;
	int		*f_color;
	int		*c_color;
	int		cc;
	int		cf;
	float	posx;
	float	posy;
	int		key_pressed;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	char	player_dir;
	int		**addr;
	void	*window;
	char	*win_addr;
	int		drawstart;
	int		pixel_bits[6];
	int		line_bytes[6];
	int		edian[6];
	double	step;
	int		w[0];
	int		h[0];
	int		texx;
	int		texy;
	double	texpos;
	int		side;
	int		**buff;
	double	oldplanex;
	int		rgbi;
	char	*check_rgb_number;
	int		counter_parsing;
	int		rgbj;
	int		*check_rgb_nb;
	int		counter;
	double	camerax;
	int		mapx;
	int		mapy;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;
	double	perpwalldist;
	double	wallx;
	int		lineheight;
	int		drawend;
	int		texdir;
}	t_data;

/* close key */

int		close_error(char *err_message, t_data *data);
int		close_window(t_data *data);
int		key(int key, t_data *data);
void	map_init(t_data *data, char *map_name);
void	free_all(t_data *data);
void	map_print(char **str);
int		parse_for_texture(t_data *data, char c, int i, int j);
int		parse_for_texture2(t_data *data, int i, int j);
int		parse_for_texture3(t_data *data, int i, int j);
int		get_floor_color(t_data *data, int i, int j);
int		get_ceiling_color(t_data *data, int i, int j);
int		check_map(t_data *data, char **file);
void	browse_image(t_data *data);
void	get_texture(t_data *data);
int		check_texture(t_data *data);
void	est_west_dir(t_data *data);
void	found_player_dir(t_data *data);
int		parse_file(t_data *data);
int		parse_map(char *str);
int		get_floor_color(t_data *data, int i, int j);
char	*cj(char *str, char c, int param);
int		check_rgb_fc(char *color, t_data *data, int param);
int		check_rgb_early(char *color, t_data *data, int param);
int		check_rgb_end(t_data *data, int param);
int		find_longest_line(char **map);
int		init_raytracing(t_data *data);
void	draw_value_init(t_data *data);
void	find_wall(t_data *d);
void	put_ceiling_in_window(t_data *data, int x, int y);
void	put_floor_in_window(t_data *data, int x, int y);

#endif
