# include "../inc/cub3d.h"

int	esc(t_data *data)
{
	//фришить map  mlx_destroy_image
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void	move_a(t_data	*data)
{
	if (data->map.map[(int)data->player.y_pos][(int)(data->player.x_pos - data->player.plane_x * MS)] == 0)
		data->player.x_pos -= data->player.plane_x * MS;
	if (data->map.map[(int)(data->player.y_pos - data->player.plane_y * MS)][(int)data->player.x_pos] == 0)
		data->player.y_pos -= data->player.plane_y * MS;
}

void	move_d(t_data	*data)
{
	if (data->map.map[(int)data->player.y_pos][(int)(data->player.x_pos + data->player.plane_x * MS)] == 0)
		data->player.x_pos += data->player.plane_x * MS;
	if (data->map.map[(int)(data->player.y_pos + data->player.plane_y * MS)][(int)data->player.x_pos] == 0)
		data->player.y_pos += data->player.plane_y * MS;
}

void	move_w(t_data	*data)
{
	if (data->map.map[(int)data->player.y_pos][(int)(data->player.x_pos + data->player.dir_x * MS)] == 0)
		data->player.x_pos += data->player.dir_x * MS;
	if (data->map.map[(int)(data->player.y_pos + data->player.dir_y * MS)][(int)(data->player.x_pos)] == 0)
		data->player.x_pos += data->player.dir_y * MS;
}

void	move_s(t_data	*data)
{
	if (data->map.map[(int)data->player.y_pos][(int)(data->player.x_pos - data->player.dir_x * MS)] == 0)
		data->player.x_pos -= data->player.dir_x * MS;
	if (data->map.map[(int)(data->player.y_pos - data->player.dir_y * MS)][(int)(data->player.x_pos)] == 0)
		data->player.x_pos -= data->player.dir_y * MS;
}


int press(int key, t_data *data)
{
	if (key == ESC)
		esc(data);
	if (key == A_KEY)
		move_a(data);
	if (key == D_KEY)
		move_d(data);
	if (key == W_KEY)
		move_w(data);
	if (key == S_KEY)
		move_s(data);
	return (0);
}

