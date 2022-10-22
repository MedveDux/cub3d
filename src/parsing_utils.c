/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:45:59 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/22 22:45:49 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_cut_line(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	rgb_dec(char *line)
{
	char	**sp;
	int		num;

	sp = ft_split(line, ',');
	num = ft_atoi(sp[2]) * 65536 + (ft_atoi(sp[1]) * 256) + ft_atoi(sp[0]);
	clean_cut_line(sp);
	return (num);
}

char	*cut_line(char *line)
{
	int		i;
	char	*new_line;
	int		size;

	size = ft_strlen(line);
	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	new_line = ft_substr(line, i, size - i - 1);
	return (new_line);
}

void	check_params2(t_data *data, char *line)
{
	char	*str;

	if (ft_strncmp(line, "F", 1) == 0)
	{
		str = cut_line(line);
		data->img.color[0] = rgb_dec(str);
		free(str);
		data->img.flag++;
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		str = cut_line(line);
		data->img.color[1] = rgb_dec(str);
		free(str);
		data->img.flag++;
	}
}

int	check_params(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		data->img.dir_names[0] = cut_line(line);
		data->img.flag++;
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		data->img.dir_names[1] = cut_line(line);
		data->img.flag++;
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		data->img.dir_names[2] = cut_line(line);
		data->img.flag++;
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		data->img.dir_names[3] = cut_line(line);
		data->img.flag++;
	}
	check_params2(data, line);
	return (0);
}

int	check_empty(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || i == data->map.height - 1 || \
		j == data->map.width - 1)
		return (1);
	if (data->map.map[i - 1][j] == 2 || \
		data->map.map[i + 1][j] == 2 || \
		data->map.map[i][j - 1] == 2 || \
		data->map.map[i][j + 1] == 2)
		return (1);
	return (0);
}

int	checking_elem(t_data *data, int i, int j)
{
	if (data->map.map[i][j] == 0)
	{
		if (check_empty(data, i, j))
			return (1);
	}
	return (0);
}

int	map_validation(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (checking_elem(data, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
