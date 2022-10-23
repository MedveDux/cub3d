/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:52:34 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/22 22:41:32 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	new_strlen(const char *s)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			flag++;
		i++;
	}
	if (flag > 0)
		i--;
	return (i);
}

void	init_value(t_data *data, int *i, int *j)
{
	*i = 0;
	*j = 0;
	data->map.e = 0;
	data->map.n = 0;
	data->map.s = 0;
	data->map.w = 0;
	data->player.x_pos = 0;
	data->player.y_pos = 0;
}

void	body(t_data *data, char *line, int i, int *j)
{
	if (*j > new_strlen(line) - 1)
		data->map.map[i][*j] = 2;
	else if (line[*j] == ' ')
		data->map.map[i][*j] = 2;
	else if (line[*j] == '1')
		data->map.map[i][*j] = 1;
	else if (line[*j] == '0')
		data->map.map[i][*j] = 0;
	else if (line[*j] == 'W')
		west(data, i, *j);
	else if (line[*j] == 'E')
		east(data, i, *j);
	else if (line[*j] == 'N')
		north(data, i, *j);
	else if (line[*j] == 'S')
		sourth(data, i, *j);
	(*j)++;
}

int	check_nwse(t_data *data)
{
	if (data->map.e + data->map.s + data->map.n + data->map.w > 1 || \
	data->map.e + data->map.s + data->map.n + data->map.w == 0)
		return (42);
	return (0);
}

int	init_map(char *filename, t_data *data)
{
	char	*line;
	int		i;
	int		j;
	int		fd;

	init_value(data, &i, &j);
	fd = open(filename, O_RDONLY, 0644);
	data->map.map = malloc ((data->map.height) * sizeof(int *));
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '1' || *line == ' ' || *line == '0')
		{
			data->map.map[i] = malloc((data->map.width) * sizeof(int));
			while (j < data->map.width)
				body(data, line, i, &j);
			j = 0;
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (check_nwse(data));
}
