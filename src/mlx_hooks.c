# include "../inc/cub3d.h"

int	esc(t_data *data)
{
	//фришить map  mlx_destroy_image
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}


//mlx_loop_hook
// void	ft_move(t_data *m, int x, int y)
// {
// 	char	move;

// 	move = m->map.map[y * m->map.width + x];
// 	if (move == '1' || (move == 'E' && m->map.flags.coin > 0))
// 		return ;
// 	if (m->enemy.x == x && m->enemy.y == y)
// 	{
// 		ft_putstr_fd("You died! ", 1);
// 		ft_putnbr_fd(m->steps, 1);
// 		ft_putstr_fd(" steps!\n", 1);
// 		ft_exit(m);
// 	}
// 	ft_image(move, m, x, y);
// 	m->player.y = y;
// 	m->player.x = x;
// 	m->steps++;
// 	ft_putstr_fd("Move: ", 1);
// 	ft_putnbr_fd(m->steps, 1);
// 	ft_putstr_fd("\n", 1);
// }



int press(int key, t_keys *keys)
{
	if (key == ESC)
		keys->exit = true;
	if (key == A_KEY)
		keys->left = true;
	if (key == D_KEY)
		keys->right = true;
	if (key == W_KEY)
		keys->forward = true;
	if (key == S_KEY)
		keys->back = true;
	return (0);
	
	// сразу на функцию esc???
	// 	if (key == ESC)
	// 	esc(data);
	// else if (key == D_KEY)
	// 	ft_move(data, data->player.x_pos + 1, data->player.y_pos);
	// else if (key == A_KEY)
	// 	ft_move(data, data->player.x_pos - 1, data->player.y_pos);
	// else if (key == W_KEY)
	// 	ft_move(data, data->player.x_pos, data->player.y_pos - 1);
	// else if ( key == S_KEY)
	// 	ft_move(data, data->player.x_pos, data->player.y_pos + 1);
}

int	unhold(int key, t_keys	*keys)
{
	if (key == ESC)
		keys->exit = false;
	if (key == A_KEY)
		keys->left = false;
	if (key == D_KEY)
		keys->right = false;
	if (key == W_KEY)
		keys->forward = false;
	if (key == S_KEY)
		keys->back = false;
	return (0);
}
