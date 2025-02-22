/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:38:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 12:05:09 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_put_pixel(t_fdf *fdf, float x, float y, int color)
{
	int	i;

	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		i = ((int)y * fdf->size_line) + ((int)x * (fdf->bpp / 8));
		*(unsigned int *)(fdf->data_addr + i) = color;
	}
}

void	ft_rotate_x(float *y, float *z, double x_angle)
{
	float	y_start;

	y_start = *y;
	*y = y_start * cos(x_angle) + *z * sin(x_angle);
	*z = y_start * -sin(x_angle) + *z * cos(x_angle);
}

void	ft_rotate_y(float *x, float *z, double y_angle)
{
	int	x_start;

	x_start = *x;
	*x = x_start * cos(y_angle) + *z * sin(y_angle);
	*z = x_start * -sin(y_angle) + *z * cos(y_angle);
}

void	ft_rotate_z(float *x, float *y, double z_angle)
{
	t_dot	start;

	start.y = *y;
	start.x = *x;
	*y = start.x * sin(z_angle) + start.y * cos(z_angle);
	*x = start.x * cos(z_angle) - start.y * sin(z_angle);
}
