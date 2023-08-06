/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:38 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/06 20:49:06 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	destroy_fun()
{
	exit (3);
}
int	mouse_press(t_var *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}


void	my_mlx_pixel_put(t_var *data, int x, int y, int color)
{
	char	*dst;
	// if (x > 0 && y > 0 && x < x_width(data->map2d) && y < y_height(data->map2d))
	// {
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	// }
}


void	first_draw_line(t_var *data)
{
	double dx;
	double dy;
	
	int x;
	int y;
	double step;
	double x_inc;
	double y_inc;
	double	x_nearest;
	double	y_nearest;
	int i;
	
	i = 0;
	data->player_pos.angle_in_radian = PI;
    data->player_pos.save_x_inc = cos(data->player_pos.angle_in_radian) * LINE_LENTH;
    data->player_pos.save_y_inc = sin(data->player_pos.angle_in_radian) * LINE_LENTH;
	
	dx = data->player_pos.x_line_end - data->player_pos.line_x_start;
	dy = data->player_pos.y_line_end - data->player_pos.line_y_start;


	// y_nearest = data->player_pos.player_y - ((data->tmp_player_y / 50) * 50);
	// x_nearest = y_nearest / tan(data->player_pos.angle_in_radian);

	// data->player_pos.x_line_end = cos(data->player_pos.angle_in_radian) * x_nearest;
	// data->player_pos.y_line_end = sin(data->player_pos.angle_in_radian) * y_nearest;
	// y_nearest += data->player_pos.player_y;
	// x_nearest += data->player_pos.player_x;
	// dx = data->player_pos.x_line_end - data->player_pos.line_x_start;
	// dy = data->player_pos.y_line_end - data->player_pos.line_y_start;
	
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	
	while (i <= step)
	{
		if (data->map2d[(int)data->player_pos.line_y_start / 50][(int)data->player_pos.line_x_start / 50] != '1')
		{
				my_mlx_pixel_put(data, (int)data->player_pos.line_x_start, (int)data->player_pos.line_y_start, 0x00000000);
				// data->player_pos.line_x_start = data->player_pos.player_x; 
				// data->player_pos.line_y_start = data->player_pos.player_y;
			data->player_pos.line_x_start += x_inc;
			data->player_pos.line_y_start += y_inc;
		}
		i++;
	}
}


void	draw_line(t_var *data)
{
	double dx;
	double dy;
	
	int x;
	int y;
	double step;
	double x_inc;
	double y_inc;
	double	x_nearest;
	double	y_nearest;
	int i;
	
	i = 0;
	// data->player_pos.angle_in_radian = PI;
    // data->player_pos.save_x_inc = cos(data->player_pos.angle_in_radian) * LINE_LENTH;
    // data->player_pos.save_y_inc = sin(data->player_pos.angle_in_radian) * LINE_LENTH;
	data->player_pos.line_x_start = data->player_pos.player_x; 
	data->player_pos.line_y_start = data->player_pos.player_y;
	dx = data->player_pos.x_line_end - data->player_pos.line_x_start;
	dy = data->player_pos.y_line_end - data->player_pos.line_y_start;


	// y_nearest = data->player_pos.player_y - ((data->tmp_player_y / 50) * 50);
	// x_nearest = y_nearest / tan(data->player_pos.angle_in_radian);

	// data->player_pos.x_line_end = cos(data->player_pos.angle_in_radian) * x_nearest;
	// data->player_pos.y_line_end = sin(data->player_pos.angle_in_radian) * y_nearest;
	// y_nearest += data->player_pos.player_y;
	// x_nearest += data->player_pos.player_x;
	// dx = data->player_pos.x_line_end - data->player_pos.line_x_start;
	// dy = data->player_pos.y_line_end - data->player_pos.line_y_start;
	
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	
	while (i <= step)
	{
		if (data->player_pos.x_line_end > 0 && data->player_pos.y_line_end > 0)
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
}

void	horizotal_ray(t_var *data)
{
	double alpha_y;
	double alpha_x;
	double dy;
	double dx;
	double tmp;


	
	double ys;
	double xs;
	double old_xs;
	double old_ys;
	
	if(sin(data->player_pos.angle_in_radian) == 0 || cos(data->player_pos.angle_in_radian) == 0)
		return;
	alpha_y = floor((int)data->player_pos.player_y / GRIDE_SIZE) * 50 - 1;
	dy = data->player_pos.player_y - alpha_y;
	alpha_x = fabs(dy / tan(data->player_pos.angle_in_radian));
	if (data->player_pos.angle_in_radian >= 1.5708 && data->player_pos.angle_in_radian <= 4.71239)
	{
		alpha_x = data->player_pos.player_x - alpha_x;
	}
	else 
		alpha_x = data->player_pos.player_x + alpha_x;
	
	// if (data->player_pos.angle_in_radian >= 0 && data->player_pos.angle_in_radian <= 1.5708)
	// 	ys = GRIDE_SIZE;	
	// else
	// 	ys = -GRIDE_SIZE;
	
	printf("alpha_x=%d\n",(int)alpha_x / GRIDE_SIZE);
	printf("alpha_y=%d\n",(int)alpha_y / GRIDE_SIZE);
	printf("x=%d\n",x_width(data->map2d));
	printf("y=%d\n",y_height(data->map2d));
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           	old_ys = ys;
	old_xs = xs;
	if (alpha_x < 0 || alpha_y < 0 || alpha_y > x_width(data->map2d) || alpha_x > y_height(data->map2d))
		return;
	else if (data->map2d[(int)alpha_y / GRIDE_SIZE][(int)alpha_x /GRIDE_SIZE] != '1')
	{
		data->player_pos.x_line_end = alpha_x;
		data->player_pos.y_line_end = alpha_y;
		draw_line(data);
	}
	// else
	// {
	// 	xs = xs + alpha_x;
	// 	ys = ys + alpha_y;
	// 	while (1)
	// 	{
	// 		if (xs < 0 || ys < 0 || xs > x_width(data->map2d) || ys > y_height(data->map2d))
	// 			break;
	// 		if (data->map2d[(int)xs / 50][(int)ys / 50])
	// 		{
	// 			data->player_pos.x_line_end = xs;
	// 			data->player_pos.y_line_end = ys;
	// 			return (draw_line(data));		
	// 		}
	// 		// else
	// 		// {
	// 			xs = old_xs + xs;
	// 			ys = old_ys + ys;
	// 		// }
	// 	}
	// }
	// data->player_pos.x_line_end = alpha_x;
	// data->player_pos.y_line_end = alpha_y;
	// draw_line(data);
	
}

void	virtical_ray(t_var *data)
{
	double alpha_y;
	double alpha_x;
	double dy;
	double dx;
	double tmp;

	double ys;
	double xs;

	// printf("test\n");
	if(sin(data->player_pos.angle_in_radian) == 0 || cos(data->player_pos.angle_in_radian) == 0)
		return;
		
	ys = GRIDE_SIZE;
	alpha_x = floor((int)data->player_pos.player_x / GRIDE_SIZE) * 50;
	printf("floor=%f\n",data->player_pos.angle_in_radian);
	// printf("floor=%d\n",(int)alpha_x);
	if(cos(data->player_pos.angle_in_radian) > 0)
		alpha_x += 50;
		
	dx = data->player_pos.player_x - alpha_x;
	alpha_y = dx * tan(data->player_pos.angle_in_radian);

	alpha_y += data->player_pos.player_y;
	data->player_pos.x_line_end = alpha_x;
	data->player_pos.y_line_end = alpha_y;
	
	// printf("player->dx  =%d\n", (int)alpha_x);
	// printf("player->dy  =%d\n", (int)dy);
	// printf("player->x  =%d\n", (int)data->player_pos.player_x);
	// printf("player->y  =%d\n", (int)data->player_pos.player_y);
	
	// if ((int)alpha_x > 0 && (int)alpha_y > 0 && (int)alpha_x < x_width(data->map2d) && (int)alpha_y < y_height(data->map2d) )
	// {
	// 	// if (data->map2d[(int)alpha_x / 50][(int)alpha_y / 50] == '1')
	// 	// {
	// 	// 	// draw_line(data);
	// 	// 	return;
	// 	// }
	// }
	draw_line(data);
}

int move_player(int i, t_var *data)
{
	data->tmp_player_x = data->player_pos.player_x;
	data->tmp_player_y  = data->player_pos.player_y;
	if (i == 53)
		destroy_fun();
	if (i == 13)
		move_forward(data);
	else if (i == 1)
		move_back(data);
	else if (i == 0)
		move_left(data);
	else if (i == 2)
		move_right(data);
	else if (i == 124)
		rotate_right(data);
	else if (i == 123)
		rotate_left(data);
	if (data->map2d[(int)data->tmp_player_y / 50][(int)data->tmp_player_x / 50] != '1')
	{
		data->player_pos.player_y  =  data->tmp_player_y;
		data->player_pos.player_x  =  data->tmp_player_x;
		data->player_pos.x_line_end = data->player_pos.player_x + data->player_pos.save_x_inc;
		data->player_pos.y_line_end = data->player_pos.player_y + data->player_pos.save_y_inc;
		rander_map2d(data);
	}
	return (1);
}


int main(int ac , char **av)
{
	int fd;
    t_var img;

    (void)ac;
	fd = open(av[1], O_RDONLY);
 	img.map2d = ftt_split(&img, fd);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, x_width(img.map2d), y_height(img.map2d), "map");
	img.img = mlx_new_image(img.mlx, x_width(img.map2d),  y_height(img.map2d));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);	
	img.player_pos.player_x = 0;
	img.player_pos.player_y = 0;
	img.player_pos.player_speed = 3;
	img.store_cos = 0;
	img.store_sin = 0;
	img.player_pos.angle_in_radian = ROTATE_ANGLE;
	
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