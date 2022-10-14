# include "../inc/cub3d.h"

void	set_textures(t_data *data)
{
	void	*img;
	int		tab[5];

	data->img.img_ptr = mlx_new_image(data->mlx, SCALE, SCALE);
	// data->img.data_addr = (int *)mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
	// 	&data->img.size_line, &data->img.endian);
	img = mlx_xpm_file_to_image(data->mlx, data->img.dir_names[3], &tab[0], &tab[1]);
	//checking function
	data->img.texturep[0] = (int *)mlx_get_data_addr(data->img.img_ptr, &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(data->mlx, data->img.dir_names[2], &tab[0], &tab[1]);
	//checking function
	data->img.texturep[1] = (int *)mlx_get_data_addr(data->img.img_ptr, &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(data->mlx, data->img.dir_names[0], &tab[0], &tab[1]);
	//checking function
	data->img.texturep[2] = (int *)mlx_get_data_addr(data->img.img_ptr, &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(data->mlx, data->img.dir_names[1], &tab[0], &tab[1]);
	//checking function
	data->img.texturep[3] = (int *)mlx_get_data_addr(data->img.img_ptr, &tab[2], &tab[3], &tab[4]);
		
}
