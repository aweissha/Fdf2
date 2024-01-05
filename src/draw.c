/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:39:15 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/05 17:00:18 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

float	max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

int	ft_calc_color(t_dot a, t_dot b, float max)
{
	float	percent;
	int		red;
	int		green;
	int		blue;
	int 	color;

	if (mod(b.x - a.x) >= mod(b.y - a.y))
		percent = (max - mod(b.x - a.x)) / max;
	else
		percent = (max - mod(b.y - a.y)) / max;
	red = ((a.color >> 16) & 0xff) + percent * (((b.color >> 16) & 0xff)-((a.color >> 16) & 0xff));
	green = ((a.color >> 8) & 0xff) + percent * (((b.color >> 8) & 0xff)-((a.color >> 8) & 0xff));	
	blue = (a.color & 0xff) + percent * ((b.color & 0xff)-(a.color & 0xff));
	color = (red << 16) + (green << 8) + blue;			
	return (color);
}

void	ft_draw_line(t_dot a, t_dot b, t_fdf *fdf)
{
	float	x_step;
	float	y_step;
	float	max_step;

	// Calculate steps
	x_step = b.x - a.x;
	y_step = b.y - a.y;
	
	max_step = max(mod(x_step), mod(y_step));
	x_step /= max_step;
	y_step /= max_step;

	while ((int)(a.x - b.x) != 0 || (int)(a.y - b.y) != 0)
	{
		ft_put_pixel(fdf, a.x, a.y, ft_calc_color(a, b, max_step));
		a.x = a.x + x_step;
		a.y = a.y + y_step;
	}
}

t_dot	ft_edit_dot(t_dot dot, t_fdf *fdf)
{
	// zoom
	dot.x *= fdf->zoom;
	dot.y *= fdf->zoom;
	dot.z *= fdf->zoom;

	// z-scaling
	dot.z *= fdf->z_scale;	

	// bring the map to the middle
	dot.x -= (fdf->map->width * fdf->zoom) / 2;
	dot.y -= (fdf->map->height * fdf->zoom) / 2;

	// Rotate around axis
	ft_rotate_x(&dot.y, &dot.z, fdf->x_angle);
	ft_rotate_y(&dot.x, &dot.z, fdf->y_angle);
	ft_rotate_z(&dot.x, &dot.y, fdf->z_angle);

	// shift
	dot.x += fdf->shift_x;
	dot.y += fdf->shift_y;

	return (dot);
}

void	ft_instructions(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 20, 0xffffff, "Left Arrow:	Move Left");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 40, 0xffffff, "Right Arrow:	Move Right");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 60, 0xffffff, "Up Arrow:	Move Up");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 80, 0xffffff, "Down Arrow:	Move Down");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 100, 0xffffff, "W/S:	X-Rotation");	
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 120, 0xffffff, "A/D:	Y-Rotation");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 140, 0xffffff, "X/C:	Z-Rotation");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 160, 0xffffff, "+/-:	Zoom");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 180, 0xffffff, "J/K:	Z-Scaling");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 10, 200, 0xffffff, "I/P:	Isometric/Parallel");
	mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 850, 1000, 0x009999, "@aweissha-studios");
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
				ft_draw_line(ft_edit_dot(fdf->map->matrix[y][x], fdf), ft_edit_dot(fdf->map->matrix[y][x + 1], fdf), fdf);
			if (y < (fdf->map->height - 1))
				ft_draw_line(ft_edit_dot(fdf->map->matrix[y][x], fdf), ft_edit_dot(fdf->map->matrix[y + 1][x], fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->mlx_img, 0, 0);
	ft_instructions(fdf);
}
