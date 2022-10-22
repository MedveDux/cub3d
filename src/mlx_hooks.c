/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:20:57 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/22 19:50:02 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// фришить map  mlx_destroy_image
int	esc(t_data *data)
{
	clear(data);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void	move_a(t_data	*data)
{
	if (data->map.map[(int)(int)(data->player.x_pos - data->player.plane_x \
	* 0.65)][(int)data->player.y_pos] == 0)
		data->player.x_pos -= data->player.plane_x * MS;
	if (data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos - \
	data->player.plane_y * 0.65)] == 0)
		data->player.y_pos -= data->player.plane_y * MS;
}

void	move_d(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos + data->player.plane_x * 0.65)] \
	[(int)data->player.y_pos] == 0)
		data->player.x_pos += data->player.plane_x * MS;
	if (data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos + \
	data->player.plane_y * 0.65)] == 0)
		data->player.y_pos += data->player.plane_y * MS;
}

void	move_w(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos + data->player.dir_x * 0.65)] \
	[(int)data->player.y_pos] == 0)
		data->player.x_pos += data->player.dir_x * MS;
	if (data->map.map[(int)(data->player.x_pos)][(int)(data->player.y_pos + \
	data->player.dir_y * 0.65)] == 0)
		data->player.y_pos += data->player.dir_y * MS;
}

void	move_s(t_data	*data)
{
	if (data->map.map[(int)(data->player.x_pos - data->player.dir_x * 0.65)] \
	[(int)data->player.y_pos] == 0)
		data->player.x_pos -= data->player.dir_x * MS;
	if (data->map.map[(int)(data->player.x_pos)][(int)(data->player.y_pos - \
	data->player.dir_y * 0.65)] == 0)
		data->player.y_pos -= data->player.dir_y * MS;
}

void	move_right(t_data	*data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(RS) - \
	data->player.dir_y * sin(RS);
	data->player.dir_y = old_dir_x * sin(RS) + data->player.dir_y * cos(RS);
	data->player.plane_x = data->player.plane_x * cos(RS) - \
	data->player.plane_y * sin(RS);
	data->player.plane_y = old_plane_x * sin(RS) + data->player.plane_y \
	* cos(RS);
}

void	move_left(t_data	*data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-RS) - \
	data->player.dir_y * sin(-RS);
	data->player.dir_y = old_dir_x * sin(-RS) + \
	data->player.dir_y * cos(-RS);
	data->player.plane_x = data->player.plane_x * cos(-RS) - \
	data->player.plane_y * sin(-RS);
	data->player.plane_y = old_plane_x * sin(-RS) + \
	data->player.plane_y * cos(-RS);
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

int	press(int key, t_data *data)
{
	if (key == ESC)
		esc(data);
	else if (key == A_KEY)
		move_a(data);
	else if (key == D_KEY)
		move_d(data);
	else if (key == W_KEY)
		move_w(data);
	else if (key == S_KEY)
		move_s(data);
	else if (key == RIGHT_KEY)
		move_right(data);
	else if (key == LEFT_KEY)
		move_left(data);
	else if (key == M_KEY)
	{
		if (data->player.map_flag == 0)
			data->player.map_flag = 1;
		else
			data->player.map_flag = 0;
	}
	return (0);
}
