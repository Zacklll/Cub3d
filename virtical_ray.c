/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:51:45 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/10 18:52:56 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	virtical_ray(t_var *data)
{
	double alpha_y;
	double alpha_x;
	double dy;
	double dx;
	double ys;
	double xs;
	double old_xs;
	double old_ys;
	
	// data->player_pos.x_virtical_line_end = INT_MAX ;
	// data->player_pos.y_virtical_line_end = INT_MAX ;
	//if(sin(data->player_pos.ray_angle) == 0 || cos(data->player_pos.ray_angle) == 0)
		//return;
	if (data->player_pos.ray_angle >= convert_dgree(90) && data->player_pos.ray_angle <= convert_dgree(270))
		alpha_x = (floor((int)data->player_pos.player_x / GRIDE_SIZE) * 50) - 1;
	else
		alpha_x = (floor((int)data->player_pos.player_x / GRIDE_SIZE) * 50) + 50;

	alpha_y =  (alpha_x - data->player_pos.player_x) * tan(data->player_pos.ray_angle);

	if (data->player_pos.ray_angle >= 0 && data->player_pos.ray_angle <= convert_dgree(180))
		alpha_y = data->player_pos.player_y + fabs(alpha_y);
	else 
		alpha_y = data->player_pos.player_y - fabs(alpha_y);
	
	if (data->player_pos.ray_angle >= convert_dgree(90) && data->player_pos.ray_angle <=  convert_dgree(270))
		xs = -GRIDE_SIZE;
	else
		xs = GRIDE_SIZE;
		
	ys = xs * tan(data->player_pos.ray_angle);
	if (alpha_x < 0 || alpha_y < 0 || alpha_x > x_width(data->map2d) || alpha_y > y_height(data->map2d))
	{
		data->player_pos.x_virtical_line_end = INT_MAX ;
		data->player_pos.y_virtical_line_end = INT_MAX ;
		return;
	}
	if (data->map2d[(int)alpha_y / GRIDE_SIZE][(int)alpha_x /GRIDE_SIZE] == '1')
	{
		data->player_pos.x_virtical_line_end = alpha_x;
		data->player_pos.y_virtical_line_end = alpha_y;
	}
	else
	{
		old_xs = xs + alpha_x;
		old_ys = alpha_y + ys;
		while (1)
		{
			if (old_xs < 0)
				old_xs = xs;
			if (old_ys < 0)
				old_ys = ys;
			if (old_xs > 0 && old_ys > 0 && old_xs < x_width(data->map2d) && old_ys < y_height(data->map2d))
			{
				if (data->map2d[(int)old_ys / 50][(int)old_xs  / 50] != '1')
				{
					old_xs += xs;
					old_ys += ys;
				}
				else if (data->map2d[(int)old_ys  / 50][(int)old_xs / 50] == '1')
				{
					data->player_pos.x_virtical_line_end = old_xs;
					data->player_pos.y_virtical_line_end = old_ys;
					break;
				}
			}
			else
			{
				data->player_pos.x_virtical_line_end = INT_MAX;
				data->player_pos.y_virtical_line_end = INT_MAX;
				return;
			}
		}
	}
}
