/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:47:49 by mdaryn            #+#    #+#             */
/*   Updated: 2022/10/23 16:21:59 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_celling_and_floor(t_data *data)
{
	unsigned int		*dst;
	int					i;

	dst = (unsigned int *)data->img.data_addr;
	i = SCALE * SCALE / 2 + 1;
	while (--i > 0)
	*dst++ = data->img.color[0];
	i = SCALE * SCALE / 2 + 1;
	while (--i > 0)
	*dst++ = data->img.color[1];
}

void	init_start_params(t_data *data, int i)
{
	data->ray.camera_x = 2 * i / (double)SCALE - 1;
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x \
	* data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y \
	* data->ray.camera_x;
	data->ray.map_x = (int)data->player.x_pos;
	data->ray.map_y = (int)data->player.y_pos;
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_dist_x = 1e30;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_dist_y = 1e30;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

void	calculate_steps(t_data	*data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.x_pos - data->ray.map_x) * \
		data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.x_pos) * \
		data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.y_pos - data->ray.map_y) * \
		data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.y_pos) * \
		data->ray.delta_dist_y;
	}
}

void	dda_algoritm(t_data	*data)
{
	data->ray.hit = 0;
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map.map[data->ray.map_x][data->ray.map_y] == 1)
			data->ray.hit = 1;
	}
}

void	draw_func_helper(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = (data->ray.side_dist_x - \
		data->ray.delta_dist_x);
	else
		data->ray.perp_wall_dist = (data->ray.side_dist_y - \
		data->ray.delta_dist_y);
	data->ray.line_height = (int)(SCALE / data->ray.perp_wall_dist);
		data->ray.draw_start = -data->ray.line_height / 2 + SCALE / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + SCALE / 2;
	if (data->ray.draw_end >= SCALE)
		data->ray.draw_end = SCALE - 1;
}
