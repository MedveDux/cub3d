# include "../inc/cub3d.h"

int	esc(t_data *data)
{
	//фришить map  mlx_destroy_image
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}


//mlx_loop_hook
void	ft_move(t_data *data, char word)
{
	char	move;

	if (data->map.map[(int)(data->player.y_pos)][(int)(data->player.x_pos- \
	data->player.plane_x * MS)] == 0)
		data->player.x_pos -= data->player.plane_x * MS;
	if (data->map.map[(int)(data->player.y_pos - data->player.plane_y * MS)] \
	[(int)(data->player.plane_x)] == 0)
		data->player.y_pos -= data->player.plane_y * MS;


void	move_d(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos + data->player.plane_x * 0.65)][(int)data->player.y_pos] == 0)
		data->player.x_pos += data->player.plane_x * MS;
	if (data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos + data->player.plane_y * 0.65)] == 0)
		data->player.y_pos += data->player.plane_y * MS;
}

}



int press(int key, t_data *data)
{
	// if (key == ESC)
	// 	keys->exit = true;
	// if (key == A_KEY)
	// 	keys->left = true;
	// if (key == D_KEY)
	// 	keys->right = true;
	// if (key == W_KEY)
	// 	keys->forward = true;
	// if (key == S_KEY)
	// 	keys->back = true;

	
	// сразу на функцию esc???
	if (key == ESC)
		esc(data);
	else if (key == D_KEY)
		ft_move(data, 'D');
	else if (key == A_KEY)
		ft_move(data,'A');
	else if (key == W_KEY)
		ft_move(data, 'W');
	else if ( key == S_KEY)
		ft_move(data, 'S');
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
	return (0);
}

