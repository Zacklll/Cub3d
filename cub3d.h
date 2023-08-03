/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-wad <zael-wad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:59 by zael-wad          #+#    #+#             */
/*   Updated: 2023/08/02 18:24:30 by zael-wad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>

typedef struct t_player
{
	double 		save_y_inc;
	double 		save_x_inc;
			
	double 		line_x_start;
	double 		line_y_start;
	int			player_x;
	int			player_y;
	int			map2d_x;
	int			map2d_y;
	double			x_line_end;
	double 		y_line_end;
	double		angle_in_radian;
}				t_player;

typedef struct t_var
{
	// int             x_width;
	// int             y_height;

	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player_pos;
	char		**tmp_arry;
	char		**tmp_arry2;
	void		*mlx;
	char		**map2d;
	void		*mlx_win;
}				t_var;

char			**ft_split(char const *st, char c);
char			**cpy(char const *st, char **str, char c);
char			**sto(char const *st, char **str, char c);
int				wdcount(char const *s2, char c, int i);
int				x_width(char **p);
int				y_height(char **p);
char			*ft_strjoin_split(char *s1, char *s2);
char			*ft_join(int fd);
char			**ftt_split(t_var *data, int fd);
char			*join_utils(char *s1);
// mao2d

void			fill_wall(t_var *img, int x, int y);
void			fill_ground(t_var *img, int x, int y, int key);
void			player_fill(t_var *img, int x, int y);

void			my_mlx_pixel_put(t_var *data, int x, int y, int color);
void			update_player_pos(t_var *img, int x, int y, int key);

void	first_fill_ground(t_var *img, int x, int y);

#endif