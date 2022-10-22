/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:10 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/22 20:23:14 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_pixel(t_data *data, int i, int j, int color)
{
	int		y;
	int		x;
	char	*dest;

	y = SCALE * 0.01 * i;
	while (y < SCALE * 0.01 * (i + 1))
	{
		x = SCALE * 0.01 * j;
		while (x < SCALE * 0.01 * (j + 1))
		{
			dest = (char *)data->img.data_addr + ((y + 10) * \
			data->img.size_line + (x + 10) * (data->img.bpp / 8));
			*(unsigned int *)dest = color;
			x++;
		}
		y++;
	}
}

void	draw_mini_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == 1)
				draw_pixel(data, i, j, 65407);
			else
				draw_pixel(data, i, j, 789516);
			j++;
		}
		i++;
	}
	draw_pixel(data, data->player.x_pos, data->player.y_pos, 7905);
}
