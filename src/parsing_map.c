# include "../inc/cub3d.h"

int	new_strlen(const char *s)
{
	int	i;
	int flag;

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

int init_map(char *filename, t_data *data) 
{
    int i;
    int j;
    int fd;
    char *line;

    i = 0;
    j = 0;
	data->map.e = 0;
	data->map.n = 0;
	data->map.s = 0;
	data->map.w = 0;
	data->player.x_pos = 0;
	data->player.y_pos = 0;
    fd = open(filename,  O_RDONLY, 0644);
    data->map.map = malloc ((data->map.height) * sizeof(int *));
    line = get_next_line(fd);
    while (line)
    {
        if (*line == '1' || *line == ' ' || *line == '0')
        {
            data->map.map[i] = malloc((data->map.width) * sizeof(int));
            while (j < data->map.width)
            {
				if (j > new_strlen(line) - 1)
					data->map.map[i][j] = 2;
                else if (line[j] == ' ')
                    data->map.map[i][j] = 2;
                else if (line[j] == '1')
                    data->map.map[i][j] = 1;
                else if (line[j] == '0')
                    data->map.map[i][j] = 0;
                else if (line[j] == 'W')
                {
                    data->map.map[i][j] = 0;
                    data->map.n++;
					data->player.x_pos = i;
					data->player.y_pos = j;
					data->player.dir_x = 0;
					data->player.dir_y = -1;
					data->player.plane_x = 0.66;
					data->player.plane_y = 0;
					// data->player.angle = 270;
                }
                else if (line[j] == 'E')
                {
                    data->map.map[i][j] = 0;
                    data->map.s++;
					data->player.x_pos = i;
					data->player.y_pos = j;
					data->player.dir_x = 0;
					data->player.dir_y = 1;
					data->player.plane_x = -0.66;
					data->player.plane_y = 0;
					// data->player.angle = 90;
                }
                else if (line[j] == 'N')
                {
                    data->map.map[i][j] = 0;
                    data->map.w++;
					data->player.x_pos = i;
					data->player.y_pos = j;
					data->player.dir_x = -1;
					data->player.dir_y = 0;
					data->player.plane_x = 0;
					data->player.plane_y = -0.66;
					// data->player.angle = 180;
                }
                else if (line[j] == 'S')
                {
                    data->map.map[i][j] = 0;
                    data->map.e++;
					data->player.x_pos = i;
					data->player.y_pos = j;
					data->player.dir_x = 1;
					data->player.dir_y = 0;
					data->player.plane_x = 0;
					data->player.plane_y = 0.66;
					// data->player.angle = 0;
                }
				j++;
            }
            j = 0;
			i++;
        }
		 free(line);
		line = get_next_line(fd);
		 
    }
	 free(line);
    close(fd);

	if (data->map.e + data->map.s + data->map.n + data->map.w > 1 ||
		data->map.e + data->map.s + data->map.n + data->map.w == 0)
		return (42);

	// function_valid добавить контур из 2 и сделать проверку на то, что рядом с 0 нет 2
	return (0);
}