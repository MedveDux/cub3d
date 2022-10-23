/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:31:05 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/23 15:44:38 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../src/get_next_line/get_next_line.h"
# include "../minilibx/mlx.h"
# define SCALE 1000
# define T_SIZE 64
# define MS 0.25
# define RS 0.20

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
	M_KEY = 46
};

typedef struct s_keys
{
	bool		forward;
	bool		back;
	bool		right;
	bool		left;
	bool		exit;
}	t_keys;

typedef struct s_img
{
	char		*dir_names[4];
	char		*texture_addr[4];
	void		*img_texturing_xpm[5];
	int			flag;
	int			color[2];
	void		*img_ptr;
	int			*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
}	t_img;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		mouse_x;
	int		map_flag;
}	t_player;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;	
}	t_raycast;

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
	int		n;
	int		s;
	int		e;
	int		w;
}	t_map;

typedef struct s_wall
{
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
}	t_wall;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
	t_keys		keys;
	t_raycast	ray;
	t_wall		wall;
}	t_data;

int		mouse_hook(int x, int y, t_data *data);
int		parsing(char *filename, t_data *data);
int		check_params(t_data *data, char *line);
int		init_map(char *filename, t_data *data);
int		map_validation(t_data *data);
int		esc(t_data *data);
int		press(int key, t_data *data);
int		game_loop(t_data	*data);
void	set_textures(t_data *data);
void	draw_mini_map(t_data *data);
void	clear(t_data *data);
void	west(t_data *data, int i, int j);
void	east(t_data *data, int i, int j);
void	north(t_data *data, int i, int j);
void	sourth(t_data *data, int i, int j);
void	init_parsing(t_data *data, size_t *size, int *i);
void	move_a(t_data	*data);
void	move_s(t_data	*data);
void	move_d(t_data	*data);
void	move_w(t_data	*data);
void	clear(t_data *data);
void	clean_cut_line(char **arr);
void	draw_celling_and_floor(t_data *data);
void	init_start_params(t_data *data, int i);
void	calculate_steps(t_data	*data);
void	dda_algoritm(t_data	*data);
void	draw_func_helper(t_data *data);
int		rgb_dec(char *line);
char	*cut_line(char *line);
void	check_params2(t_data *data, char *line);
int		check_params(t_data *data, char *line);
int		norma(t_data *data, char *filename);
#endif
