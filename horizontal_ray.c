/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:53:23 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/10 18:53:45 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	horizotal_ray(t_var *data)
{
	double alpha_y;
	double alpha_x;
	double dy;
	double dx;
	double ys;
	double xs;
	double old_xs;
	double old_ys;

	// data->player_pos.x_horizontal_line_end = INT_MAX - 1;
	// data->player_pos.y_horizontal_line_end = INT_MAX - 1;
	//if(sin(data->player_pos.ray_angle) == 0 || cos(data->player_pos.ray_angle) == 0)
		// return;

	if (data->player_pos.ray_angle > 0 && data->player_pos.ray_angle <=  convert_dgree(180))
		alpha_y = (floor((int)data->player_pos.player_y / GRIDE_SIZE) * 50) + 50;
	else
		alpha_y = (floor((int)data->player_pos.player_y / GRIDE_SIZE) * 50) - 1;
	
	alpha_x =  (data->player_pos.player_y - alpha_y) / tan(data->player_pos.ray_angle);

	if (data->player_pos.ray_angle >=  convert_dgree(90) && data->player_pos.ray_angle <= convert_dgree(270))
		alpha_x = data->player_pos.player_x - fabs(alpha_x);
	else 
		alpha_x = data->player_pos.player_x + fabs(alpha_x);
	
	if (data->player_pos.ray_angle >= 0 && data->player_pos.ray_angle <= convert_dgree(180))
		ys = GRIDE_SIZE;	
	else
		ys = -GRIDE_SIZE;
                                                     
	xs = ys / tan(data->player_pos.ray_angle);
		
	if (alpha_x < 0 || alpha_y < 0 || alpha_x > x_width(data->map2d) || alpha_y > y_height(data->map2d))
	{
		data->player_pos.x_horizontal_line_end = INT_MAX - 1;
		data->player_pos.y_horizontal_line_end = INT_MAX - 1;
		return;
	}
	if (data->map2d[(int)alpha_y / GRIDE_SIZE][(int)alpha_x /GRIDE_SIZE] == '1')
	{
		data->player_pos.x_horizontal_line_end = alpha_x;
		data->player_pos.y_horizontal_line_end = alpha_y;
	}
	else
	{
		old_xs = xs + alpha_x;
		old_ys = alpha_y + ys;
		while(1)
		{
			if (old_xs < 0)
				old_xs = GRIDE_SIZE;
			if (old_ys < 0)
				old_ys = GRIDE_SIZE;
			if (old_xs > 0 && old_ys > 0 && old_xs < x_width(data->map2d) && old_ys < y_height(data->map2d))
			{
				if (data->map2d[(int)old_ys  / 50][(int)old_xs  / 50] != '1')
				{
					old_xs += xs;
					old_ys += ys;
				}
				else if (data->map2d[(int)old_ys  / 50][(int)old_xs  / 50] == '1')
				{
					data->player_pos.x_horizontal_line_end = old_xs;
					data->player_pos.y_horizontal_line_end = old_ys;
					break;
				}
			}
			else
			{
				data->player_pos.x_horizontal_line_end = INT_MAX - 1;
				data->player_pos.y_horizontal_line_end = INT_MAX - 1;
				return;
			}
		}
	}
}
