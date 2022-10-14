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
	   data->ray.deltaDistY = fabs(1 / data->ray.rayDirX);
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
        if(data->map.map[data->ray.mapX][data->ray.mapY] > 0) // приравнять к 1 в случае чего
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
		draw_twxtures(data, i);
		
		
		
		// switch (data->map.map[data->ray.mapX][data->ray.mapY])
		// {
		// 	case 1:
		// 		// color;
		// 		break;
		// }
// 3 строчки закоментил
		// if(side == 1) 
		// 	color = color / 2;
		// verLine(i, drawStart, drawEnd, color); // write function

		// oldTime = time;
    	// time = getTicks();
    	// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    	// print(1.0 / frameTime); //FPS counter
    	// redraw();
    	// cls();

		//speed modifiers
    	// double moveSpeed = 5.0; //the constant value is in squares/second
   	 	// double rotSpeed = 3.0; //the constant value is in radians/second
		
		
//мой комент
		//readKeys();


// мой комент
/*		if(keyDown(SDLK_UP))
    	{
      		if(data->map.map[(int)(data->player.x_pos + data->player.dir_x * moveSpeed)][(int)data->player.y_pos] == false)
			  data->player.x_pos += data->player.dir_x * moveSpeed;
      		if(data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos + data->player.dir_y * moveSpeed)] == false)
			  data->player.y_pos += data->player.dir_y * moveSpeed;
    	}
    	//move backwards if no wall behind you
   		if(keyDown(SDLK_DOWN))
    	{
      		if(data->map.map[(int)(data->player.x_pos - data->player.dir_x  * moveSpeed)][(int)data->player.y_pos] == false)
			  data->player.x_pos -= data->player.dir_x * moveSpeed;
      		if(data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos - data->player.dir_y * moveSpeed)] == false) 
			  data->player.y_pos -= data->player.dir_y * moveSpeed;
    	}
    	//rotate to the right
    	if(keyDown(SDLK_RIGHT))
    	{
      	//both camera direction and camera plane must be rotated
      	double oldDirX = data->player.dir_x;
      	data->player.dir_x = data->player.dir_x * cos(-rotSpeed) - data->player.dir_y * sin(-rotSpeed);
      	data->player.dir_y = oldDirX * sin(-rotSpeed) + data->player.dir_y * cos(-rotSpeed);
      	double oldPlaneX = data->player.plane_x;
      	data->player.plane_x = data->player.plane_x * cos(-rotSpeed) - data->player.plane_y * sin(-rotSpeed);
      	data->player.plane_y = oldPlaneX * sin(-rotSpeed) + data->player.plane_y * cos(-rotSpeed);
    	}
    	//rotate to the left
    	if(keyDown(SDLK_LEFT))
    	{
      	//both camera direction and camera plane must be rotated
      	double oldDirX = data->player.dir_x;
      	data->player.dir_x = data->player.dir_x * cos(rotSpeed) - data->player.dir_y * sin(rotSpeed);
      	data->player.dir_y = oldDirX * sin(rotSpeed) + data->player.dir_y  * cos(rotSpeed);
      	double oldPlaneX = data->player.plane_x;
      	data->player.plane_x = data->player.plane_x * cos(rotSpeed) - data->player.plane_y * sin(rotSpeed);
      	data->player.plane_y = oldPlaneX * sin(rotSpeed) + data->player.plane_y * cos(rotSpeed);
    	}
*/
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
	return (0);
}



// void	draw_func(t_data *data)
// {
// 	int i;
	
// 	i = 0;
// 	while ( i < SCALE)
// 	{
// 		init_start_params(&data, i);
// 		// data->ray.cameraX = 2 * i / (double)SCALE - 1;
// 		// data->ray.rayDirX = data->player.dir_x + data->player.plane_x * data->ray.cameraX;
// 		// data->ray.rayDirY = data->player.dir_y + data->player.plane_y * data->ray.cameraX;
//       	// data->ray.mapX = (int)data->player.x_pos;
//      	// data->ray.mapY = (int)data->player.y_pos;
// 		// if (data->ray.rayDirX == 0)
// 		// 	data->ray.deltaDistX = 1e30;
// 		// else
// 		// 	data->ray.deltaDistX = abs(1 / data->ray.rayDirX);
// 	   	// if (data->ray.rayDirY == 0)
// 		//    data->ray.deltaDistY = 1e30;
// 	   	// else
// 		//    data->ray.deltaDistY = abs(1 / data->ray.rayDirX);

// 		calculate_steps(&data);
// 	//    if( data->ray.rayDirX < 0)
//     //   {
//     //     data->ray.stepX = -1;
//     //     data->ray.sideDistX = (data->player.x_pos -  data->ray.mapX) *  data->ray.deltaDistX;
//     //   }
//     //   else
//     //   {
//     //     data->ray.stepX = 1;
//     //     data->ray.sideDistX = ( data->ray.mapX + 1.0 - data->player.x_pos) *  data->ray.deltaDistX;
//     //   }
//     //   if( data->ray.rayDirY < 0)
//     //   {
//     //     data->ray.stepY = -1;
//     //     data->ray.sideDistY = (data->player.y_pos -  data->ray.mapY) *  data->ray.deltaDistY;
//     //   }
//     //   else
//     //   {
//     //     data->ray.stepY = 1;
//     //     data->ray.sideDistY = ( data->ray.mapY + 1.0 - data->player.y_pos) *  data->ray.deltaDistY;
//     //   }
	
// 	dda_algoritm(&data);
// 	//   data->ray.hit = 0; 
//     //   while(data->ray.hit == 0)
//     //   {
//     //     //jump to next map square, either in x-direction, or in y-direction
//     //     if(data->ray.sideDistX < data->ray.sideDistY)
//     //     {
//     //       data->ray.sideDistX += data->ray.deltaDistX;
//     //       data->ray.mapX += data->ray.stepX;
//     //       data->ray.side = 0;
//     //     }
//     //     else
//     //     {
//     //       data->ray.sideDistY += data->ray.deltaDistY;
//     //       data->ray.mapY += data->ray.stepY;
//     //       data->ray.side = 1;
//     //     }
// 	// 	//Check if ray has hit a wall
//     //     if(data->map.map[data->ray.mapX][data->ray.mapY] > 0) // приравнять к 1 в случае чего
// 	// 		data->ray.hit = 1;
// 	//   }

// 	draw_func_helper(&data);
// 		// next function
// 	//   if(data->ray.side == 0)
// 	//   	data->ray.perpWallDist = (data->ray.sideDistX - data->ray.deltaDistX);
//     //   else
// 	//   	data->ray.perpWallDist = (data->ray.sideDistY - data->ray.deltaDistY);

// 	// 	data->ray.lineHeight = (int)(SCALE / data->ray.perpWallDist);
// 	// 	data->ray.drawStart = -data->ray.lineHeight / 2 + SCALE / 2;
// 	// 	if(data->ray.drawStart < 0)
// 	// 		data->ray.drawStart = 0;
// 	// 	data->ray.drawEnd = data->ray.lineHeight / 2 + SCALE / 2;
// 	// 	if(data->ray.drawEnd >= SCALE)
// 	// 		data->ray.drawEnd = SCALE - 1;
		
		
		
		
// 		// switch (data->map.map[data->ray.mapX][data->ray.mapY])
// 		// {
// 		// 	case 1:
// 		// 		// color;
// 		// 		break;
// 		// }
// // 3 строчки закоментил
// 		// if(side == 1) 
// 		// 	color = color / 2;
// 		// verLine(i, drawStart, drawEnd, color); // write function

// 		// oldTime = time;
//     	// time = getTicks();
//     	// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
//     	// print(1.0 / frameTime); //FPS counter
//     	// redraw();
//     	// cls();

// 		//speed modifiers
//     	// double moveSpeed = 5.0; //the constant value is in squares/second
//    	 	// double rotSpeed = 3.0; //the constant value is in radians/second
		
		
// //мой комент
// 		//readKeys();


// // мой комент
// /*		if(keyDown(SDLK_UP))
//     	{
//       		if(data->map.map[(int)(data->player.x_pos + data->player.dir_x * moveSpeed)][(int)data->player.y_pos] == false)
// 			  data->player.x_pos += data->player.dir_x * moveSpeed;
//       		if(data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos + data->player.dir_y * moveSpeed)] == false)
// 			  data->player.y_pos += data->player.dir_y * moveSpeed;
//     	}
//     	//move backwards if no wall behind you
//    		if(keyDown(SDLK_DOWN))
//     	{
//       		if(data->map.map[(int)(data->player.x_pos - data->player.dir_x  * moveSpeed)][(int)data->player.y_pos] == false)
// 			  data->player.x_pos -= data->player.dir_x * moveSpeed;
//       		if(data->map.map[(int)data->player.x_pos][(int)(data->player.y_pos - data->player.dir_y * moveSpeed)] == false) 
// 			  data->player.y_pos -= data->player.dir_y * moveSpeed;
//     	}
//     	//rotate to the right
//     	if(keyDown(SDLK_RIGHT))
//     	{
//       	//both camera direction and camera plane must be rotated
//       	double oldDirX = data->player.dir_x;
//       	data->player.dir_x = data->player.dir_x * cos(-rotSpeed) - data->player.dir_y * sin(-rotSpeed);
//       	data->player.dir_y = oldDirX * sin(-rotSpeed) + data->player.dir_y * cos(-rotSpeed);
//       	double oldPlaneX = data->player.plane_x;
//       	data->player.plane_x = data->player.plane_x * cos(-rotSpeed) - data->player.plane_y * sin(-rotSpeed);
//       	data->player.plane_y = oldPlaneX * sin(-rotSpeed) + data->player.plane_y * cos(-rotSpeed);
//     	}
//     	//rotate to the left
//     	if(keyDown(SDLK_LEFT))
//     	{
//       	//both camera direction and camera plane must be rotated
//       	double oldDirX = data->player.dir_x;
//       	data->player.dir_x = data->player.dir_x * cos(rotSpeed) - data->player.dir_y * sin(rotSpeed);
//       	data->player.dir_y = oldDirX * sin(rotSpeed) + data->player.dir_y  * cos(rotSpeed);
//       	double oldPlaneX = data->player.plane_x;
//       	data->player.plane_x = data->player.plane_x * cos(rotSpeed) - data->player.plane_y * sin(rotSpeed);
//       	data->player.plane_y = oldPlaneX * sin(rotSpeed) + data->player.plane_y * cos(rotSpeed);
//     	}
// */
// 		i++;
// 	}
// }
