/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:30:45 by cyelena           #+#    #+#             */
/*   Updated: 2022/10/20 20:06:31 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/cub3d.h"

int mlx_start(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
        //clear data
		ft_putstr_fd("Wrong filename!", 2);
		return (EXIT_FAILURE);
	}
	// mlx_get_screen_size(&data.screen_width, &data.screen_height);
	// printf("%d\n",data.screen_width);
	data->win = mlx_new_window(data->mlx, SCALE,
			SCALE, "cub3d");
	if (data->win == NULL)
	{
        //clear data
		ft_putstr_fd("Wrong filename!", 2);
		return (EXIT_FAILURE);
	}

	set_textures(data);
	mlx_hook(data->win, 17, 0, esc, data);
	mlx_hook(data->win, 2, 0, press, data);
    // mlx_hook(data->win, 6, 0, mouse_hook, game);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_loop(data->mlx);
	return (0);
}

int main(int argc, char **argv)
{
    t_data data;
    int size;

    if (argc != 2)
	{
		ft_putstr_fd("Wrong number of arguments!", 2);
		return (EXIT_FAILURE);
	}
    size = ft_strlen(argv[1]);
    if (size <= 4 || argv[1][size - 1] != 'b' || argv[1][size - 2] != 'u' || argv[1][size - 3] != 'c' || argv[1][size - 4] != '.')
    {
        ft_putstr_fd("Wrong filename!", 2);
		return (EXIT_FAILURE);
    }
    if (parsing(argv[1], &data) == 42)
    {
        return (EXIT_FAILURE);//putstr??
    }  
    printf("Direction 1 %s\n", data.img.dir_names[0]);
    printf("Direction 2 %s\n", data.img.dir_names[1]);
    printf("Direction 3 %s\n", data.img.dir_names[2]);
    printf("Direction 4 %s\n", data.img.dir_names[3]);
    printf("Flag: %d\n", data.img.flag);
    printf("Color 1 %d\n", data.img.color[0]);
    printf("Color 2 %d\n", data.img.color[1]);
    printf("Height: %d\n", data.map.height);
    printf("Width: %d\n", data.map.width);
	printf("START\n");
	int i = 0;
	int j = 0;
	while(i < data.map.height)
	{
		while (j < data.map.width)
		{
			printf("%d", data.map.map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	mlx_start(&data);
    return (0);
}
 
int parsing(char *filename, t_data *data)
{
    int fd;
    char    *line;
    int     i;
    size_t    size;
    
    size = 0;
    i = 0;
    fd = open(filename, O_RDONLY, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("Wrong fd\n", 2);
        close(fd);
        return (42);
    }
    data->img.flag = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (check_params(data, line) == 42)
            return (42);// maybe убрать
        if (data->img.flag == 6 && (*line == '1' || *line == ' '))
        {
            i++;
            if (size < ft_strlen(line) - 1)
            size = ft_strlen(line) - 1;
            
        }
        line = get_next_line(fd);
    }
    data->map.height = i;
    data->map.width = size;
    close(fd);
	if (init_map(filename, data) == 42)
		return (42);
	if (map_validation(data))
	{
		ft_putstr_fd("Invalid map\n", 2);
		// clean data
		return (42);	
	}
    return (0);
}
