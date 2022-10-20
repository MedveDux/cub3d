# include "../inc/cub3d.h"


int	esc(t_data *data)
{
	//фришить map  mlx_destroy_image
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}


void	move_a(t_data	*data)
{
	if (data->map.map[(int)(int)(data->player.x_pos - data->player.plane_x * 0.65)][(int)data->player.y_pos] == 0)
		data->player.x_pos -= data->player.plane_x * MS;
	if (data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos - data->player.plane_y * 0.65)] == 0)
		data->player.y_pos -= data->player.plane_y * MS;
}

void	move_d(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos + data->player.plane_x * 0.65)][(int)data->player.y_pos] == 0)
		data->player.x_pos += data->player.plane_x * MS;
	if (data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos + data->player.plane_y * 0.65)] == 0)
		data->player.y_pos += data->player.plane_y * MS;
}

void	move_w(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos + data->player.dir_x * 0.65)][(int)data->player.y_pos] == 0)
		data->player.x_pos += data->player.dir_x * MS;
	if (data->map.map[(int)(data->player.x_pos)][(int)(data->player.y_pos + data->player.dir_y * 0.65)] == 0)
		data->player.y_pos += data->player.dir_y * MS;
}

void	move_s(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos - data->player.dir_x * 0.65)][(int)data->player.y_pos] == 0)
		data->player.x_pos -= data->player.dir_x * MS;
	if (data->map.map[(int)(data->player.x_pos)][(int)(data->player.y_pos - data->player.dir_y * 0.65)] == 0)
		data->player.y_pos -= data->player.dir_y * MS;
}

void	move_right(t_data	*data)
{
	double oldDirX = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(RS) - data->player.dir_y * sin(RS);
	data->player.dir_y = oldDirX * sin(RS) + data->player.dir_y * cos(RS);
	double oldPlaneX = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(RS) - data->player.plane_y * sin(RS);
	data->player.plane_y = oldPlaneX * sin(RS) + data->player.plane_y * cos(RS);
}

void	move_left(t_data	*data)
{
	double oldDirX = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-RS) - data->player.dir_y * sin(-RS);
	data->player.dir_y = oldDirX * sin(-RS) + data->player.dir_y * cos(-RS);
	double oldPlaneX = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-RS) - data->player.plane_y * sin(-RS);
	data->player.plane_y = oldPlaneX * sin(-RS) + data->player.plane_y * cos(-RS);
}

int	mouse_hook(int x, int y, t_data *data)
{
	(void) y;
	if (x > data->player.mouse_x)
		move_right(data);
	else if (x < data->player.mouse_x)
		move_left(data);
	data->player.mouse_x = x;
	return (0);
}

int press(int key, t_data *data)
{
	printf("Key: %d\n", key);
	// printf("Plane x: %f\n", data->player.plane_x);
	// printf("Plane y: %f\n", data->player.plane_y);
	// printf("Dir x: %f\n", data->player.dir_x);
	// printf("Dir y: %f\n", data->player.dir_y);
	// printf("Ray dir x: %f\n", data->ray.rayDirX);
	// printf("Ray dir y: %f\n", data->ray.rayDirY);
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
	if (key == RIGHT_KEY)
		move_right(data);
	if (key == LEFT_KEY)
		move_left(data);
	return (0);
}

