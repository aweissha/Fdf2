/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:39:15 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/03 15:56:12 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define MAX(a, b) (a > b ? a : b)

float	mod(float i)
{
	return (i < 0) ? -i : i;
}

void	ft_draw_line(t_dot a, t_dot b, t_fdf *fdf)
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
				ft_draw_line(ft_make_dot(x, y, fdf), ft_make_dot(x + 1, y, fdf), fdf);
			if (y < (fdf->map->height - 1))
				ft_draw_line(ft_make_dot(x, y, fdf), ft_make_dot(x, y + 1, fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->mlx_img, 0, 0);
	ft_instructions(fdf);
}
