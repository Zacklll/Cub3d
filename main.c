/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:38 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/02 19:48:06 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>


int	mouse_press(t_var *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}


void	my_mlx_pixel_put(t_var *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	cast_line(t_var *data)
{
	int dx;
	int dy;
	
	int x;
	int y;
	int step;
	double x_inc;
	double y_inc;
	int i;
	
	i = 0;
	data->player_pos.line_x_start = data->player_pos.player_x; 
	data->player_pos.line_y_start = data->player_pos.player_y;
	dx = data->player_pos.x_line_end -  data->player_pos.line_x_start;
	dy = data->player_pos.y_line_end -  data->player_pos.line_y_start;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	
	x_inc = (double)dx / step;
	y_inc = (double)dy / step;
	
	// printf("%f==\n" ,data->player_pos.line_x_start + x_inc);
	// printf("end--====%f==\n",data->player_pos.y_line_end );
	
	while (i <= step)
	{
		if (data->map2d[(int)data->player_pos.line_y_start / 50][(int)data->player_pos.line_x_start / 50] != '1')
		{
				my_mlx_pixel_put(data, (int)data->player_pos.line_x_start, (int)data->player_pos.line_y_start, 0x00000000);
			data->player_pos.line_x_start += x_inc;
			data->player_pos.line_y_start += y_inc;
		}
		i++;
	}
}

int	first_rander_map2d(t_var *img)
{
	
	img->player_pos.map2d_x = 0;
	while (img->map2d[img->player_pos.map2d_x])
	{
		img->player_pos.map2d_y = 0;
		while (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y])
		{
			if (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y] == '1')
				fill_wall(img,(img->player_pos.map2d_x + 1) * 50,  (img->player_pos.map2d_y + 1) * 50);
			else if (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y] == '0')
				first_fill_ground(img,  (img->player_pos.map2d_x + 1) * 50, (img->player_pos.map2d_y + 1) * 50);
			else if (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y] == 'P')
				player_fill(img, (img->player_pos.map2d_x + 1) * 50,  (img->player_pos.map2d_y + 1) * 50);
			img->player_pos.map2d_y++;
		}
		img->player_pos.map2d_x++;
	}
	cast_line(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

// void	cast_line(t_var *data)
// {
// 	double	dx;
// 	double	dy;
// 	int		steps;
// 	double	x_inc;
// 	double	y_inc;

// 	dx = data->player_pos.x_line_end -  data->player_pos.player_x;
// 	dy = data->player_pos.y_line_end -  data->player_pos.player_y;
// 	if (fabs(dx) > fabs(dy))
// 		steps = fabs(dx);
// 	else
// 		steps = fabs(dy);
// 	x_inc = dx / steps;
// 	y_inc = dy / steps;
// 	dx = data->player_pos.player_x;
// 	dy = data->player_pos.player_y;
// 	while (steps >= 0)
// 	{
// 		my_mlx_pixel_put(data, (int)((dx)), (int)((dy)), 0x00000000);
// 		dx += x_inc;
// 		dy += y_inc;
// 		steps--;
// 	}
// }


int	rander_map2d(t_var *img, int key)
{
	img->player_pos.map2d_x = 0;
	while (img->map2d[img->player_pos.map2d_x])
	{
		img->player_pos.map2d_y = 0;
		while (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y ])
		{
			if (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y ] == '1')
				fill_wall(img,(img->player_pos.map2d_x + 1) * 50,  (img->player_pos.map2d_y  + 1) * 50);
			else if (img->map2d[img->player_pos.map2d_x][img->player_pos.map2d_y ] != '1')
				fill_ground(img,  (img->player_pos.map2d_x + 1) * 50, (img->player_pos.map2d_y + 1) * 50, key);
			img->player_pos.map2d_y++;
		}
		img->player_pos.map2d_x++;
	}
	cast_line(img);
	my_mlx_pixel_put(img, img->player_pos.player_x, img->player_pos.player_y,0x00000000);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

int move_player(int i, t_var *data)
{
	// if (i == 53)
		// destroy_fun(data);
	int x;
	int y;
	double y_inc;
	double x_inc;
	x = data->player_pos.player_x;
	y  = data->player_pos.player_y;
	if (i == 1)
	{
		y  = data->player_pos.player_y - 1;
		// move_up();
	}
	else if (i == 13)
	{
		y  = data->player_pos.player_y + 1;
		// move_down();
	}
	else if (i == 0)
	{
		x  = data->player_pos.player_x + 1;
		// move_right();
	}
	else if (i == 2)
	{
		x  = data->player_pos.player_x - 1;
		// move_left();
	}
	else if (i == 124)
	{	
		data->player_pos.angle_in_radian += 0.1;
		data->player_pos.save_x_inc = cos(data->player_pos.angle_in_radian) * 30;
		data->player_pos.save_y_inc = sin(data->player_pos.angle_in_radian) * 30;
		
		data->player_pos.x_line_end = data->player_pos.player_x  + data->player_pos.save_x_inc;
		data->player_pos.y_line_end =  data->player_pos.player_y + data->player_pos.save_y_inc;
	}
	else if (i == 123)
	{	
		data->player_pos.angle_in_radian -= 0.1;
		
		data->player_pos.save_x_inc = cos(data->player_pos.angle_in_radian) * 30;
		data->player_pos.save_y_inc = sin(data->player_pos.angle_in_radian) * 30;
		
		data->player_pos.x_line_end = data->player_pos.player_x + data->player_pos.save_x_inc;
		data->player_pos.y_line_end =  data->player_pos.player_y + data->player_pos.save_y_inc;
	}
	
	data->player_pos.x_line_end = data->player_pos.player_x + 	data->player_pos.save_x_inc;
	data->player_pos.y_line_end =  data->player_pos.player_y +  data->player_pos.save_y_inc;
	if (data->map2d[y / 50][x / 50] != '1')
	{
		data->player_pos.player_y  = y;
		data->player_pos.player_x  = x;
		rander_map2d(data, i);
	}
	
	return (1);
}


int main(int ac , char **av)
{
 	// void	*mlx;
	// void	*mlx_win;
	int fd;
    t_var img;
	// t_player *data;

    (void)ac;
	// img = malloc(sizeof(t_var));
	fd = open(av[1], O_RDONLY);
 	img.map2d = ftt_split(&img, fd);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, x_width(img.map2d), y_height(img.map2d), "map");
	img.img = mlx_new_image(img.mlx, x_width(img.map2d),  y_height(img.map2d));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);	
	img.player_pos.player_x = 0;
	img.player_pos.player_y = 0;
	
	// img.player_pos.angle_in_radian = 0.1;
	
	
	// mlx_loop_hook(img.mlx , rander_map2d, &img);
	first_rander_map2d(&img);
	// img.player_pos.x_line_end = img.player_pos.player_x + cos(img.player_pos.angle_in_radian) * 30;
	// img.player_pos.y_line_end = img.player_pos.player_y + sin(img.player_pos.angle_in_radian) * 30;
	mlx_hook(img.mlx_win, 2, 1L<<1, move_player, &img);
	// mlx_key_hook(mlx_ptr.win, key_press, &mlx_ptr);
	// mlx_hook(img.mlx_win, player_);
	mlx_loop(img.mlx);
	// free(&img);
	// mlx_destroy_window(&img.mlx, &img.mlx_win);
}