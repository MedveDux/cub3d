# include "../inc/cub3d.h"



void	draw_celling_and_floor(t_data *data)
{
	unsigned int *dst;
	int	i;

	dst = (unsigned int *)data->img.data_addr;
	i =  SCALE * SCALE / 2 + 1;
	while(--i > 0)
	*dst++ = data->img.color[0];
	i =  SCALE * SCALE / 2 + 1;
	while(--i > 0)
	*dst++ = data->img.color[1];

}

void init_start_params(t_data *data, int i)
{
	data->ray.cameraX = 2 * i / (double)SCALE - 1;
	data->ray.rayDirX = data->player.dir_x + data->player.plane_x * data->ray.cameraX;
	data->ray.rayDirY = data->player.dir_y + data->player.plane_y * data->ray.cameraX;
    data->ray.mapX = (int)data->player.x_pos;
    data->ray.mapY = (int)data->player.y_pos;
	if (data->ray.rayDirX == 0)
			data->ray.deltaDistX = 1e30;
	else
		data->ray.deltaDistX = fabs(1 / data->ray.rayDirX);
	if (data->ray.rayDirY == 0)
	   data->ray.deltaDistY = 1e30;
	else
	   data->ray.deltaDistY = fabs(1 / data->ray.rayDirY);
}

void	calculate_steps(t_data	*data)
{
	if( data->ray.rayDirX < 0)
      {
        data->ray.stepX = -1;
        data->ray.sideDistX = (data->player.x_pos -  data->ray.mapX) *  data->ray.deltaDistX;
      }
      else
      {
        data->ray.stepX = 1;
        data->ray.sideDistX = ( data->ray.mapX + 1.0 - data->player.x_pos) *  data->ray.deltaDistX;
      }
      if( data->ray.rayDirY < 0)
      {
        data->ray.stepY = -1;
        data->ray.sideDistY = (data->player.y_pos -  data->ray.mapY) *  data->ray.deltaDistY;
      }
      else
      {
        data->ray.stepY = 1;
        data->ray.sideDistY = ( data->ray.mapY + 1.0 - data->player.y_pos) *  data->ray.deltaDistY;
      }
}

void dda_algoritm(t_data	*data)
{
	data->ray.hit = 0; 
      while(data->ray.hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(data->ray.sideDistX < data->ray.sideDistY)
        {
          data->ray.sideDistX += data->ray.deltaDistX;
          data->ray.mapX += data->ray.stepX;
          data->ray.side = 0;
        }
        else
        {
          data->ray.sideDistY += data->ray.deltaDistY;
          data->ray.mapY += data->ray.stepY;
          data->ray.side = 1;
        }
		//Check if ray has hit a wall
        if(data->map.map[data->ray.mapX][data->ray.mapY] == 1) // приравнять к 1 в случае чего /// х и y под большим вопросом
			data->ray.hit = 1;
	  }
}

void	draw_func_helper(t_data *data)
{
	if(data->ray.side == 0)
	  	data->ray.perpWallDist = (data->ray.sideDistX - data->ray.deltaDistX);
    else
	  	data->ray.perpWallDist = (data->ray.sideDistY - data->ray.deltaDistY);
	data->ray.lineHeight = (int)(SCALE / data->ray.perpWallDist);
	data->ray.drawStart = -data->ray.lineHeight / 2 + SCALE / 2;
	if(data->ray.drawStart < 0)
		data->ray.drawStart = 0;
	data->ray.drawEnd = data->ray.lineHeight / 2 + SCALE / 2;
	if(data->ray.drawEnd >= SCALE)
		data->ray.drawEnd = SCALE - 1;
}
void	prepare_func(t_data	*data)
{
	double	wall_x;

	if (data->ray.side == 0)
		wall_x = data->player.y_pos + data->ray.perpWallDist * data->ray.rayDirY;
	else
		wall_x = data->player.x_pos + data->ray.perpWallDist * data->ray.rayDirX;
	wall_x -= floor(wall_x);
	data->wall.tex_x = (int)(wall_x * (double)T_SIZE);
	if (data->ray.side == 0 && data->ray.rayDirX > 0)
		data->wall.tex_x = T_SIZE - data->wall.tex_x - 1;
	if (data->ray.side == 1 && data->ray.rayDirY < 0)
		 data->wall.tex_x = T_SIZE - data->wall.tex_x - 1;
	data->wall.step = 1.0 * T_SIZE / data->ray.lineHeight;
	data->wall.tex_pos = (data->ray.drawStart - SCALE / 2 + data->ray.lineHeight / 2) * data->wall.step;
}

int texturing(t_data *data, unsigned int *color)
{

	if (data->ray.side == 0)
	{
		if (data->ray.rayDirX >= 0)
			*color = ((unsigned int *)data->img.texture_addr[3])[T_SIZE * data->wall.tex_y + data->wall.tex_x];
		else
			*color = ((unsigned int *)data->img.texture_addr[2])[T_SIZE * data->wall.tex_y + data->wall.tex_x];
	}
	else
	{
		if (data->ray.rayDirY >= 0)
			*color = ((unsigned int *)data->img.texture_addr[1])[T_SIZE * data->wall.tex_y + data->wall.tex_x];
		else
			*color = ((unsigned int *)data->img.texture_addr[0])[T_SIZE * data->wall.tex_y + data->wall.tex_x];
	}
	return(*color);
}

void	draw_textures(t_data *data, int i)
{
	int	j;
	char	*dest;
	unsigned int color;
	j = data->ray.drawStart;
	prepare_func(data);
	while (j <= data->ray.drawEnd)
	{
		data->wall.tex_y = (int)data->wall.tex_pos & (T_SIZE - 1);
		data->wall.tex_pos += data->wall.step;
		color = texturing(data, &color);
		dest = (char *)data->img.data_addr + (j * data->img.size_line + i * (data->img.bpp / 8));
		*(unsigned int *)dest = color;
		j++;

	}
}

void	draw_func(t_data *data)
{
	int i;
	
	i = 0;
	while ( i < SCALE)
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
	data->img.data_addr = (int *)mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
		&data->img.size_line, &data->img.endian);
	draw_celling_and_floor(data);
	draw_func(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	return (1);
}


