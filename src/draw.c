/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:39:15 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/29 14:51:04 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define MAX(a, b) (a > b ? a : b)

float	mod(float i)
{
	return (i < 0) ? -i : i;
}

void	ft_bresenham(t_dot a, t_dot b, t_fdf *fdf)
{
	float	x_step;
	float	y_step;
	int		max;
	int		color;
	
	//Color
	if (a.color == 0xff0000 || b.color == 0xff0000)
		color = 0xff0000;
	else
		color = 0xffffff;

	// Calculate steps
	x_step = (float)b.x - (float)a.x;
	y_step = (float)b.y - (float)a.y;
	
	max = MAX(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;

	while ((int)(a.x - b.x) != 0 || (int)(a.y - b.y) != 0)
	{
		ft_put_pixel(fdf, a.x, a.y, color);
		a.x = a.x + x_step;
		a.y = a.y + y_step;
	}
}

static void	ft_rotate_x(float *y, float *z, double x_angle)
{
	float	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * -sin(x_angle) + *z * cos(x_angle);




	
	// float	prev_y;

	// prev_y = *y;
	// *y = prev_y * cos(x_angle) + *z * sin(x_angle);

	// *z = prev_y * sin(x_angle) + *z * cos(x_angle);
	
}

static void	ft_rotate_y(float *x, float *z, double y_angle)
{


	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * -sin(y_angle) + *z * cos(y_angle);

	
	// float	prev_x;

	// prev_x = *x;
	// *x = prev_x * cos(y_angle) + *z * sin(y_angle);

	// *z = prev_x * sin(y_angle) + *z * cos(y_angle);
}

static void	ft_rotate_z(float *x, float *y, double z_angle)
{
	t_dot	prev;

	prev.x = *x;
	prev.y = *y;
	*x = prev.x * cos(z_angle) - prev.y * sin(z_angle);
	*y = prev.x * sin(z_angle) + prev.y * cos(z_angle);
}

t_dot	ft_make_dot(int	x, int y, t_fdf *fdf)
{
	t_dot	dot;

	dot.z = (fdf->map->matrix)[y][x] * fdf->z_scale;
	if (dot.z != 0)
		dot.color = 0xff0000;
	else
		dot.color = 0xffffff;

	dot.x = x;
	dot.y = y;

	// Rotate around axis
	ft_rotate_x(&dot.y, &dot.z, fdf->x_angle);
	ft_rotate_y(&dot.x, &dot.z, fdf->y_angle);
	ft_rotate_z(&dot.x, &dot.y, fdf->z_angle);

	
	// zoom + shift
	dot.x *= fdf->zoom;
	dot.y *= fdf->zoom;
	dot.x += fdf->shift_x;
	dot.y += fdf->shift_y;

	return (dot);
}

void	ft_draw_map(t_fdf *fdf)
{
	int		x;
	int		y;
	
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < (fdf->map->width - 1))
				ft_bresenham(ft_make_dot(x, y, fdf), ft_make_dot(x + 1, y, fdf), fdf);
			if (y < (fdf->map->height - 1))
				ft_bresenham(ft_make_dot(x, y, fdf), ft_make_dot(x, y + 1, fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->mlx_img, 0, 0);
}
