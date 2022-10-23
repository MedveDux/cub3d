/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:40:13 by mdaryn            #+#    #+#             */
/*   Updated: 2022/10/23 14:41:26 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
