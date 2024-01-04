/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:38:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/03 10:43:04 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_put_pixel(t_fdf *fdf, float x, float y, int color)
{
	int	i;
	
	i = ((int)y * fdf->size_line) + ((int)x * (fdf->bpp / 8));
	*(unsigned int *)(fdf->data_addr + i) = color;
}

void	ft_rotate_x(float *y, float *z, double x_angle)
{
	float	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * -sin(x_angle) + *z * cos(x_angle);
}

void	ft_rotate_y(float *x, float *z, double y_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * -sin(y_angle) + *z * cos(y_angle);

}

void	ft_rotate_z(float *x, float *y, double z_angle)
{
	t_dot	prev;

	prev.x = *x;
	prev.y = *y;
	*x = prev.x * cos(z_angle) - prev.y * sin(z_angle);
	*y = prev.x * sin(z_angle) + prev.y * cos(z_angle);
}
