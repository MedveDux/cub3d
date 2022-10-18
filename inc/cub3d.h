/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:31:05 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/16 15:24:04 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../src/get_next_line/get_next_line.h"//src
# include "../minilibx/mlx.h"
# define SCALE 600
# define T_SIZE 64
# define MS 0.25

enum e_keys_code
{
	RIGHT_KEY = 124,
	LEFT_KEY = 123,
	UP_KEY = 126,
	DOWN_KEY = 125,
	D_KEY = 2,
	A_KEY = 0,
	W_KEY = 13,
	S_KEY = 1,
	ESC = 53,
};

typedef struct s_keys
{
	bool		forward;
	bool		back;
	bool		right;
	bool		left;
	bool		exit;
} t_keys;

typedef struct s_img
{
    char *dir_names[4];
	char	*texture_addr[4]; // указатели на текстуры dir_names
	void	*img_texturing_xpm[5];
    int flag;
    int color[2];
	void		*img_ptr;
	int			*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
}   t_img;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
	double	dir_x;
	double	dir_y;
	// double	speed;
	double	plane_x;
	double	plane_y;
}   t_player;

typedef struct s_raycast
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int mapX;
    int mapY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;
    double sideDistY;
	int stepX;
    int stepY;
	int hit;
	int side;
	double	perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;	
} t_raycast;

typedef struct s_map
{
    int height;
    int width;
   	char **map;
    int n;//0
    int s;//0
    int e;//0
    int w;//0
}   t_map;

typedef	struct s_wall
{
	int	tex_x;
	double step;
	double tex_pos;
	int tex_y;
} t_wall;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	// void		*img[OBJ];
    t_img img;
	t_player player;
    t_map   map;
	t_keys	keys;
	t_raycast	ray;
	t_wall	wall;
	// int screen_width;
	// int	screen_height;
}   t_data;


int parsing(char *filename, t_data *data);
int check_params(t_data *data, char *line);
int init_map(char *filename, t_data *data); //parsing_map 
int	map_validation(t_data *data);

//mlx hooks
int	esc(t_data *data);
int press(int key, t_data *data);
int	game_loop(t_data	*data);

void	set_textures(t_data *data);


	



#endif