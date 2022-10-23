/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 22:47:06 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/23 16:21:30 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	prepare_func(t_data	*data)
{
	double	wall_x;

	if (data->ray.side == 0)
		wall_x = data->player.y_pos + data->ray.perp_wall_dist \
		* data->ray.ray_dir_y;
	else
		wall_x = data->player.x_pos + data->ray.perp_wall_dist \
		* data->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	data->wall.tex_x = (int)(wall_x * (double)T_SIZE);
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		data->wall.tex_x = T_SIZE - data->wall.tex_x - 1;
	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		data->wall.tex_x = T_SIZE - data->wall.tex_x - 1;
	data->wall.step = 1.0 * T_SIZE / data->ray.line_height;
	data->wall.tex_pos = (data->ray.draw_start - SCALE / 2 + \
	data->ray.line_height / 2) * data->wall.step;
}

int	texturing(t_data *data, unsigned int *color)
{
	if (data->ray.side == 0)
	{
		if (data->ray.ray_dir_x >= 0)
			*color = ((unsigned int *)data->img.texture_addr[3])[T_SIZE \
			* data->wall.tex_y + data->wall.tex_x];
		else
			*color = ((unsigned int *)data->img.texture_addr[2])[T_SIZE \
			* data->wall.tex_y + data->wall.tex_x];
	}
	else
	{
		if (data->ray.ray_dir_y >= 0)
			*color = ((unsigned int *)data->img.texture_addr[1])[T_SIZE \
			* data->wall.tex_y + data->wall.tex_x];
		else
			*color = ((unsigned int *)data->img.texture_addr[0])[T_SIZE \
			* data->wall.tex_y + data->wall.tex_x];
	}
	return (*color);
}

void	draw_textures(t_data *data, int i)
{
	int				j;
	char			*dest;
	unsigned int	color;

	j = data->ray.draw_start;
	prepare_func(data);
	while (j <= data->ray.draw_end)
	{
		data->wall.tex_y = (int)data->wall.tex_pos & (T_SIZE - 1);
		data->wall.tex_pos += data->wall.step;
		color = texturing(data, &color);
		dest = (char *)data->img.data_addr + (j * data->img.size_line + \
		i * (data->img.bpp / 8));
		*(unsigned int *)dest = color;
		j++;
	}
}

void	draw_func(t_data *data)
{
	int	i;

	i = 0;
	while (i < SCALE)
	{
		init_start_params(data, i);
		calculate_steps(data);
		dda_algoritm(data);
		draw_func_helper(data);
		draw_textures(data, i);
		i++;
	}
}

int	game_loop(t_data	*data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, SCALE, SCALE);
	data->img.data_addr = (int *)mlx_get_data_addr(data->img.img_ptr, \
	&data->img.bpp, \
		&data->img.size_line, &data->img.endian);
	draw_celling_and_floor(data);
	draw_func(data);
	if (data->player.map_flag == 1)
		draw_mini_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	return (1);
}
