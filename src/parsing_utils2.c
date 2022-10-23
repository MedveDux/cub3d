/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:51:51 by mdaryn            #+#    #+#             */
/*   Updated: 2022/10/23 16:13:37 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	norma(t_data *data, char *filename)
{
	if (init_map(filename, data) == 42)
		return (42);
	if (map_validation(data))
	{
		ft_putstr_fd("Invalid map\n", 2);
		clear(data);
		exit(1);
	}
	return (0);
}
