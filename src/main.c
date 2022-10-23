/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:30:45 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/23 16:11:58 by mdaryn           ###   ########.fr       */
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
	data->win = mlx_new_window(data->mlx, SCALE, SCALE, "cub3D");
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

int	checking(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Wrong fd\n", 2);
		close(fd);
		return (-1);
	}
	return (fd);
}

void	check_character(t_data *data, int *i, char *line, size_t *size)
{
	check_params(data, line);
	if (data->img.flag == 6 && (*line == '1' || *line == ' '))
	{
		(*i)++;
		if (*size < ft_strlen(line) - 1)
			*size = ft_strlen(line) - 1;
	}
	free(line);
}

int	parsing(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		i;
	size_t	size;

	init_parsing(data, &size, &i);
	fd = checking(filename);
	if (fd == -1)
		return (42);
	line = get_next_line(fd);
	while (line)
	{
		check_character(data, &i, line, &size);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (data->img.flag != 6)
	{
		ft_putstr_fd("Invalid map\n", 2);
		exit(1);
	}
	data->map.height = i;
	data->map.width = size;
	return (norma(data, filename));
}
