/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:13:26 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/04 09:55:36 by aweissha         ###   ########.fr       */
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
# define W 13
# define A 0
# define S 1
# define D 2
# define X 7
# define C 8
# define J 38
# define K 40
# define I 34
# define P 35
# define ESCAPE 53


typedef struct s_dot
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_dot;

typedef struct s_map
{
	int		width;
	int 	height;
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
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	float	z_scale;
	int		shift_x;
	int		shift_y;
	int		isometric;
}	t_fdf;



t_fdf	*ft_create_fdf(char *filename);
void	ft_free_fdf(t_fdf *fdf);
void	ft_error(char *message);
void	ft_zoom(int keycode, t_fdf *fdf);
void	ft_put_pixel(t_fdf *fdf, float x, float y, int color);
int		ft_count_lines(char *filename, t_fdf *fdf);
int		ft_count_width(char *filename, t_fdf *fdf);
void	ft_fill_map(t_fdf *fdf, t_map *map, int *matrix, char *line);
void	ft_create_matrix(t_map *map, int fd, t_fdf *fdf);
void	ft_read_lines(t_map *map, int fd, t_fdf *fdf);
void	ft_read_file(t_fdf *fdf, char *filename);
void	ft_draw_line(t_dot a, t_dot b, t_fdf *fdf);
void	ft_draw_map(t_fdf *fdf);
void	ft_init(t_fdf *fdf, char *filename);
void	ft_init_fdf(t_fdf *fdf);
void	ft_init_dot(t_dot *dot);
void	ft_init_map(t_fdf *fdf);
void	ft_free_map(t_map *map);
void	ft_shift(int keycode, t_fdf *fdf);
void	ft_zoom(int keycode, t_fdf *fdf);
void	ft_rotate(int keycode, t_fdf *fdf);
void	ft_scale_z(int keycode, t_fdf *fdf);
void	ft_change_projection(int keycode, t_fdf *fdf);
void	ft_hook_control(t_fdf *fdf);
int 	ft_key_hook(int keycode, t_fdf *fdf);
void	ft_replace_img(t_fdf *fdf);
void	ft_put_pixel(t_fdf *fdf, float x, float y, int color);
void	ft_rotate_x(float *y, float *z, double x_angle);
void	ft_rotate_y(float *x, float *z, double y_angle);
void	ft_rotate_z(float *x, float *y, double z_angle);

#endif