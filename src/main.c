/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:30:45 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/22 22:26:55 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	mlx_start(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		ft_putstr_fd("Wrong filename!", 2);
		return (EXIT_FAILURE);
	}
	data->win = mlx_new_window(data->mlx, SCALE, SCALE, "cub3d");
	if (data->win == NULL)
	{
		ft_putstr_fd("Wrong filename!", 2);
		return (EXIT_FAILURE);
	}
	set_textures(data);
	data->player.mouse_x = SCALE / 2;
	mlx_hook(data->win, 17, 0, esc, data);
	mlx_hook(data->win, 2, 0, press, data);
	mlx_mouse_move(data->win, SCALE / 2, SCALE / 2);
	mlx_hook(data->win, 6, 0, mouse_hook, data);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		size;

	if (argc != 2)
	{
		ft_putstr_fd("Wrong number of arguments!", 2);
		return (EXIT_FAILURE);
	}
	size = ft_strlen(argv[1]);
	if (size <= 4 || argv[1][size - 1] != 'b' || argv[1][size - 2] != 'u' \
	|| argv[1][size - 3] != 'c' || argv[1][size - 4] != '.')
	{
		ft_putstr_fd("Wrong filename!", 2);
		return (EXIT_FAILURE);
	}
	if (parsing(argv[1], &data) == 42)
	{
		return (EXIT_FAILURE);
	}
	mlx_start(&data);
	return (0);
}

void	clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.height)
	{
		free(data->map.map[i]);
		i++;
	}
	free(data->map.map);
	free(data->img.dir_names[0]);
	free(data->img.dir_names[1]);
	free(data->img.dir_names[2]);
	free(data->img.dir_names[3]);
}

void	init_parsing(t_data *data, size_t *size, int *i)
{
	*size = 0;
	*i = 0;
	data->player.map_flag = 0;
	data->img.flag = 0;
}

int	parsing(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		i;
	size_t	size;

	init_parsing(data, &size, &i);
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Wrong fd\n", 2);
		close(fd);
		return (42);
	}
	line = get_next_line(fd);
	while (line)
	{
		check_params(data, line);
		if (data->img.flag == 6 && (*line == '1' || *line == ' '))
		{
			i++;
			if (size < ft_strlen(line) - 1)
				size = ft_strlen(line) - 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	data->map.height = i;
	data->map.width = size;
	close(fd);
	if (init_map(filename, data) == 42)
		return (42);
	if (map_validation(data))
	{
		ft_putstr_fd("Invalid map\n", 2);
		clear(data);
		return (42);
	}
	return (0);
}
