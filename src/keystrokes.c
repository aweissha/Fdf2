/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keystrokes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:22:01 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/12 10:12:44 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_shift(int keycode, t_fdf *fdf)
{
	if (keycode == ARROW_UP)
		fdf->shift_y -= 10;
	else if (keycode == ARROW_DOWN)
		fdf->shift_y += 10;
	else if (keycode == ARROW_RIGHT)
		fdf->shift_x += 10;
	else if (keycode == ARROW_LEFT)
		fdf->shift_x -= 10;
}

void	ft_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS)
		fdf->zoom += 1;
	else if (keycode == MINUS && fdf->zoom > 1)
		fdf->zoom -= 1;
}

void	ft_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == W)
		fdf->x_angle += M_PI / 100;
	else if (keycode == S)
		fdf->x_angle -= M_PI / 100;
	else if (keycode == A)
		fdf->y_angle += M_PI / 100;
	else if (keycode == D)
		fdf->y_angle -= M_PI / 100;
	else if (keycode == X)
		fdf->z_angle += M_PI / 100;
	else if (keycode == C)
		fdf->z_angle -= M_PI / 100;
}

void	ft_scale_z(int keycode, t_fdf *fdf)
{
	if (keycode == J)
		fdf->z_scale += 0.05;
	else if (keycode == K)
		fdf->z_scale -= 0.05;
}

void	ft_change_projection(int keycode, t_fdf *fdf)
{
	if (keycode == I)
	{
		fdf->x_angle = -0.458393;
		fdf->y_angle = -0.439823;
		fdf->z_angle = 0.691150;
		fdf->isometric = 1;
	}
	else if (keycode == P)
	{
		fdf->x_angle = -0.458393;
		fdf->y_angle = -0.439823;
		fdf->z_angle = 0;
		fdf->isometric = 0;
	}
}
