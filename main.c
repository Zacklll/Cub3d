/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:38 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/12 20:54:50 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <limits.h>

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
	if (x > 0 && y > 0 && x < x_width(data->map2d) && y < y_height(data->map2d))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
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
				my_mlx_pixel_put(data, (int)data->player_pos.line_x_start, (int)data->player_pos.line_y_start, BLACK);
				// data->player_pos.line_x_start = data->player_pos.player_x; 
				// data->player_pos.line_y_start = data->player_pos.player_y;
			data->player_pos.line_x_start += x_inc;
			data->player_pos.line_y_start += y_inc;
		}
		i++;
	}
}


void	draw_line(t_var *data, int x_pos)
{
	int 		x;
	int 		y;
	double 		dx;
	double 		dy;
	double 		step;
	double 		x_inc;
	double 		y_inc;
	double		x_nearest;
	double		y_nearest;
	int i;
	
	i = 0;

	double Projected_Slice_Height;
	double wall_center;
	double hight;
	double start;
	
	virtical_ray(data);
	horizotal_ray(data);
	clac_player_distence(data);
	Projected_Slice_Height = 50 / data->player_pos.distance * data->distance_to_projection_plane;
	hight = y_height(data->map2d);
	wall_center = (hight/ 2);
	start = wall_center - (Projected_Slice_Height / 2);
	dx = x_pos;
	dy =  Projected_Slice_Height;
	
	step = fabs(dy);
	y_inc = dy / step;
	
	while (i <= step)
	{
		my_mlx_pixel_put(data, x_pos, (int)start ,BLACK);
		// x_pos += x_inc;
		start += y_inc;
		i++;
	}
}

void	player_direction(t_var *data)
{
	int x;
	int y;
	double dx;
	double dy;
	double step;
	double x_inc;
	double y_inc;
	double	x_nearest;
	double	y_nearest;
	int i;
	
	
	i = 0;
    data->player_pos.save_x_inc = cos(data->player_pos.angle_in_radian) * LINE_LENTH;
    data->player_pos.save_y_inc = sin(data->player_pos.angle_in_radian) * LINE_LENTH;
	x_nearest = data->player_pos.player_x + data->player_pos.save_x_inc;
	y_nearest = data->player_pos.player_y + data->player_pos.save_y_inc;
	data->player_pos.line_x_start = data->player_pos.player_x; 
	data->player_pos.line_y_start = data->player_pos.player_y;
	dx = x_nearest - data->player_pos.line_x_start;
	dy = y_nearest - data->player_pos.line_y_start;
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
					my_mlx_pixel_put(data, (int)data->player_pos.line_x_start, (int)data->player_pos.line_y_start,BLACK);
				data->player_pos.line_x_start += x_inc;
				data->player_pos.line_y_start += y_inc;
			}
			i++;
		}
		
	}
}
void	clac_projextion_distance(t_var *data)
{
	data->distance_to_projection_plane = tan(convert_dgree(30)) * (x_width(data->map2d) / 2);
}

void	draw_sky(t_var *data)
{
	int i;
	int j;
	i = 0;
	j = 0;

	while (i < x_width(data->map2d))
	{
		j = 0;
		while (j < y_height(data->map2d))
		{
			if (j < y_height(data->map2d) / 2)
				my_mlx_pixel_put(data,i,j,CYAN);
			else
				my_mlx_pixel_put(data,i,j,GROUND);
			j++;
		}
		i++;
	}	
}

void	player_view_filed(t_var *data)
{
	double tmp;
	double start;
	double end;



	int i;
	i = 0;
	clac_projextion_distance(data);
	draw_sky(data);
	data->player_pos.ray_angle = data->player_pos.angle_in_radian;
	while (i < x_width(data->map2d) / 2)
	{
		data->player_pos.ray_angle -= 0.00097869158;
		if (data->player_pos.ray_angle < 0)
			data->player_pos.ray_angle = 2 * PI;
		i++;
	}
	i = 0;
	while (i < x_width(data->map2d))
	{
		if (data->player_pos.ray_angle > 2 * PI)
			data->player_pos.ray_angle = 0;
		data->player_pos.ray_angle += 0.00097869158;
		draw_line(data, i);
		i++;
	}
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	// player_direction(data);
}


// void	draw_wall(t_var *data, double distance)
// {
// 	double Projected_Slice_Height;
// 	Projected_Slice_Height = 50 / distance * 400;
// 	int wall_center = y_hight(data->map2d) / 2;
	
// 	double start;
// 	start = wall_center - (Projected_Slice_Height / 2);
// 	int i = 0;
// 	while (start < Projected_Slice_Height)
// 	{
		
// 	}

// }

int move_player(int i, t_var *data)
{
	data->tmp_player_x = data->player_pos.player_x;
	data->tmp_player_y = data->player_pos.player_y;
	
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
	if (data->tmp_player_x < 0 || data->tmp_player_y < 0 || data->tmp_player_x > x_width(data->map2d) || data->tmp_player_y > y_height(data->map2d))
		return 1;
	if (data->map2d[(int)data->tmp_player_y / 50][(int)data->tmp_player_x / 50] != '1')
	{
		
		data->player_pos.player_y  =  data->tmp_player_y;
		data->player_pos.player_x  =  data->tmp_player_x;
		rander_map2d(data);
	}
	return (1);
}

double	convert_dgree(int degree)
{
	return (degree * (PI / 180));
}

void	initlize_varibles(t_var *data)
{
	data->player_pos.player_x = 0;
	data->player_pos.pd = 0;
	data->player_pos.pe = 0;
	data->player_pos.player_y = 0;
	data->player_pos.player_speed = 3;
	data->player_pos.angle_in_radian = convert_dgree(0);
	data->player_pos.x_virtical_line_end = 0;
	data->player_pos.y_virtical_line_end = 0;
	data->player_pos.x_horizontal_line_end = 0;
	data->player_pos.y_horizontal_line_end = 0;
	data->player_pos.ray_angle = 0;
	data->player_pos.line_lenth = 0;
	data->store_cos = 0;
	data->store_sin = 0;
	data->player_pos.angle_in_radian = 0;

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
	// printf("%d=x\n",x_width(img.map2d));
	// printf("%d=y\n",y_height(img.map2d));
	img.img = mlx_new_image(img.mlx, x_width(img.map2d),  y_height(img.map2d));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);	
	initlize_varibles(&img);
	first_rander_map2d(&img);
	mlx_hook(img.mlx_win, 2, 1L<<1, move_player, &img);
	// mlx_key_hook(mlx_ptr.win, key_press, &mlx_ptr);
	// mlx_hook(img.mlx_win, player_);
	mlx_loop(img.mlx);
	free(&img);
	mlx_destroy_window(&img.mlx, &img.mlx_win);
}