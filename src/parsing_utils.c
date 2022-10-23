/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:45:59 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/23 16:16:19 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
			{
				ft_putstr_fd("Invalid map\n", 2);
				exit(1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
