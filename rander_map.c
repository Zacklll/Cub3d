/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:45:34 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/06 20:47:42 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	first_rander_map2d(t_var *img)
{
	
	img->player_pos.map2d_y = 0;
	while (img->map2d[img->player_pos.map2d_y])
	{
		img->player_pos.map2d_x = 0;
		while (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x])
		{
			if (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x] == '1')
				fill_wall(img,(img->player_pos.map2d_y + 1) * 50,  (img->player_pos.map2d_x + 1) * 50);
			else if (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x] == '0')
				first_fill_ground(img,  (img->player_pos.map2d_y + 1) * 50, (img->player_pos.map2d_x + 1) * 50);
			else if (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x] == 'P')
				player_fill(img, (img->player_pos.map2d_y + 1) * 50,  (img->player_pos.map2d_x + 1) * 50);
			img->player_pos.map2d_y++;
		}
		img->player_pos.map2d_y++;
	}
	img->player_pos.x_line_end = img->player_pos.player_x + 30;
	img->player_pos.y_line_end = img->player_pos.player_y + 30;
	// first_draw_line(img);
	my_mlx_pixel_put(img, img->player_pos.player_x, img->player_pos.player_y,0x00000000);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

int	rander_map2d(t_var *img)
{
	img->player_pos.map2d_y = 0;
	while (img->map2d[img->player_pos.map2d_y])
	{
		img->player_pos.map2d_x = 0;
		while (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x ])
		{
			if (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x ] == '1')
				fill_wall(img,(img->player_pos.map2d_y + 1) * 50,  (img->player_pos.map2d_x  + 1) * 50);
			else if (img->map2d[img->player_pos.map2d_y][img->player_pos.map2d_x ] != '1')
				fill_ground(img,  (img->player_pos.map2d_y + 1) * 50, (img->player_pos.map2d_x + 1) * 50);
			img->player_pos.map2d_x++;
		}
		img->player_pos.map2d_y++;
	}
	horizotal_ray(img);
	// virtical_ray(img);
	// draw_line(img);
	my_mlx_pixel_put(img, img->player_pos.player_x, img->player_pos.player_y,0x00000000);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}
