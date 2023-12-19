/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:13:26 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/19 16:04:29 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define WIDTH 1024
# define HEIGHT 1024

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MINUS 27
# define PLUS 24
// # define SPACE 49
// # define KEY_R 15
// # define MOUSE_CLICK_LEFT 1
// # define MOUSE_CLICK_RIGHT 2
// # define MOUSE_CLICK_MIDDLE 3
// # define MOUSE_WHEEL_UP 4
// # define MOUSE_WHEEL_DOWN 5
# define ESCAPE 53


// typedef struct s_point
// {
// 	int	x;
// 	int	y;
// 	int	z;
// 	int	color;
// }	t_point;

// typedef struct s_cam
// {
// 	float	radius;
// 	double	theta_angle;
// 	double	theta_min;	
// 	double	theta_max;
// 	double	horizontal_angle;
// 	double	horizontal_angle_max;
// 	double	horizontal_angle_min;
// }	t_cam;

typedef struct s_map
{
	int	width;
	int height;
	int	**matrix;
}	t_map;


typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	t_map	*map;
	// t_cam	*cam;
}	t_fdf;



void	ft_error(char *message);
void	ft_handle_arrows(int keycode, t_fdf *fdf);
void	ft_zoom(int keycode, t_fdf *fdf);
void	ft_put_pixel(t_fdf *fdf, int x, int y, int color);
int		ft_count_lines(char *filename);
int		ft_count_width(char *filename);
void	ft_fill_x(t_map *map, int *matrix, char *line);
void	ft_create_matrix(t_map *map, int fd);
void	ft_fill_map(t_map *map);


#endif