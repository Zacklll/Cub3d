/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:24:26 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/02 19:01:58 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	player_fill(t_var *img, int x, int y)
{
	int i;
	int j;

	i = x - 50;
	while (i < x)
	{
		j = y - 50;
		while (j < y)
		{
			if (j % 50 == 0 || i % 50 == 0)
				my_mlx_pixel_put(img, j , i , 0x00FFFFFF);
			else if (j == y - 25 && i  == x - 25)
            {
                img->player_pos.player_x = j;
                img->player_pos.player_y = i;
				// printf("%d\n", img->player_pos.player_x);
				my_mlx_pixel_put(img, j , i , 0x00FF0000);
            }
			else
				my_mlx_pixel_put(img, j , i , 0x0000CED1);
			j++;
		}
		i++;
	}
}

void	update_player_pos(t_var *img, int x, int y, int key)
{
	int i;
	int j;

	i = x - 50;

	
	while (i < x)
	{
		j = y - 50;
		while (j < y)
		{
			if (j % 50 == 0 || i % 50 == 0)
				my_mlx_pixel_put(img, j , i , 0x00FFFFFF);
			else	
				my_mlx_pixel_put(img, j , i , 0x0000CED1);
			j++;
		}
		i++;
	}
}

void	fill_wall(t_var *img, int x, int y)
{
	int i;
	int j;

	i = x - 50;
	while (i < x)
	{
		j = y - 50;
		while (j  < y)
		{
			if (j % 50 == 0 || i % 50 == 0)
				my_mlx_pixel_put(img, j , i , 0x00FFFFFF);
			else
				my_mlx_pixel_put(img, j , i, 0x000000FF);
			j++;
		}
		i++;
	}
}


void	fill_ground(t_var *img, int x, int y, int key)
{
	int i ;
	int j ;
	
	i = x - 50;

	while (i < x)
	{
		j = y - 50;
		while (j < y)
		{
			if (j % 50 == 0 || i % 50 == 0)
				my_mlx_pixel_put(img, j , i , 0x00FFFFFF);
			else
				my_mlx_pixel_put(img, j , i , 0x0000CED1);
			j++;
		}
		i++;
	}
}

void	first_fill_ground(t_var *img, int x, int y)
{
	int i ;
	int j ;
	
	i = x - 50;
	while (i < x)
	{
		j = y - 50;
		while (j < y)
		{
			if (j % 50 == 0 || i % 50 == 0)
				my_mlx_pixel_put(img, j , i , 0x00FFFFFF);
			if (j == img->player_pos.player_x && i ==  img->player_pos.player_y)
			{
				my_mlx_pixel_put(img, j , i , 0x00FF0000);
			}
			else
				my_mlx_pixel_put(img, j , i , 0x0000CED1);
			j++;
		}
		i++;
	}
}