/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_directions_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:16:07 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/22 20:32:59 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	west(t_data *data, int i, int j)
{
	data->map.map[i][j] = 0;
	data->map.n++;
	data->player.x_pos = i;
	data->player.y_pos = j;
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;
}

void	east(t_data *data, int i, int j)
{
	data->map.map[i][j] = 0;
	data->map.s++;
	data->player.x_pos = i;
	data->player.y_pos = j;
	data->player.dir_x = 0;
	data->player.dir_y = 1;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0;
}

void	north(t_data *data, int i, int j)
{
	data->map.map[i][j] = 0;
	data->map.w++;
	data->player.x_pos = i;
	data->player.y_pos = j;
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = -0.66;
}

void	sourth(t_data *data, int i, int j)
{
	data->map.map[i][j] = 0;
	data->map.e++;
	data->player.x_pos = i;
	data->player.y_pos = j;
	data->player.dir_x = 1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
}
