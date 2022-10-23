/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:45:07 by mdaryn            #+#    #+#             */
/*   Updated: 2022/10/23 14:46:44 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
