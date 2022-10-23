/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:47:49 by mdaryn            #+#    #+#             */
/*   Updated: 2022/10/23 14:50:13 by mdaryn           ###   ########.fr       */
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
	data->ray.cameraX = 2 * i / (double)SCALE - 1;
	data->ray.rayDirX = data->player.dir_x + data->player.plane_x \
	* data->ray.cameraX;
	data->ray.rayDirY = data->player.dir_y + data->player.plane_y \
	* data->ray.cameraX;
	data->ray.mapX = (int)data->player.x_pos;
	data->ray.mapY = (int)data->player.y_pos;
	if (data->ray.rayDirX == 0)
		data->ray.deltaDistX = 1e30;
	else
		data->ray.deltaDistX = fabs(1 / data->ray.rayDirX);
	if (data->ray.rayDirY == 0)
		data->ray.deltaDistY = 1e30;
	else
		data->ray.deltaDistY = fabs(1 / data->ray.rayDirY);
}

void	calculate_steps(t_data	*data)
{
	if (data->ray.rayDirX < 0)
	{
		data->ray.stepX = -1;
		data->ray.sideDistX = (data->player.x_pos - data->ray.mapX) * \
		data->ray.deltaDistX;
	}
	else
	{
		data->ray.stepX = 1;
		data->ray.sideDistX = (data->ray.mapX + 1.0 - data->player.x_pos) * \
		data->ray.deltaDistX;
	}
	if (data->ray.rayDirY < 0)
	{
		data->ray.stepY = -1;
		data->ray.sideDistY = (data->player.y_pos - data->ray.mapY) * \
		data->ray.deltaDistY;
	}
	else
	{
		data->ray.stepY = 1;
		data->ray.sideDistY = (data->ray.mapY + 1.0 - data->player.y_pos) * \
		data->ray.deltaDistY;
	}
}

void	dda_algoritm(t_data	*data)
{
	data->ray.hit = 0;
	while (data->ray.hit == 0)
	{
		if (data->ray.sideDistX < data->ray.sideDistY)
		{
			data->ray.sideDistX += data->ray.deltaDistX;
			data->ray.mapX += data->ray.stepX;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sideDistY += data->ray.deltaDistY;
			data->ray.mapY += data->ray.stepY;
			data->ray.side = 1;
		}
		if (data->map.map[data->ray.mapX][data->ray.mapY] == 1)
			data->ray.hit = 1;
	}
}

void	draw_func_helper(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.perpWallDist = (data->ray.sideDistX - data->ray.deltaDistX);
	else
		data->ray.perpWallDist = (data->ray.sideDistY - data->ray.deltaDistY);
	data->ray.lineHeight = (int)(SCALE / data->ray.perpWallDist);
		data->ray.drawStart = -data->ray.lineHeight / 2 + SCALE / 2;
	if (data->ray.drawStart < 0)
		data->ray.drawStart = 0;
	data->ray.drawEnd = data->ray.lineHeight / 2 + SCALE / 2;
	if (data->ray.drawEnd >= SCALE)
		data->ray.drawEnd = SCALE - 1;
}
