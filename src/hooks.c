/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:30:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 12:02:39 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_close(t_fdf *fdf)
{
	ft_free_fdf(fdf);
	exit(0);
}

int	ft_key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		ft_close(fdf);
	else if (keycode == ARROW_UP || keycode == ARROW_DOWN
		|| keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
		ft_shift(keycode, fdf);
	else if (keycode == PLUS || keycode == MINUS)
		ft_zoom(keycode, fdf);
	else if (keycode == W || keycode == A || keycode == S
		|| keycode == D || keycode == X || keycode == C)
		ft_rotate(keycode, fdf);
	else if (keycode == J || keycode == K)
		ft_scale_z(keycode, fdf);
	else if (keycode == I || keycode == P)
		ft_change_projection(keycode, fdf);
	ft_draw_map(fdf);
	return (0);
}

void	ft_hook_control(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_window, 2, 0, ft_key_hook, fdf);
	mlx_hook(fdf->mlx_window, 17, 0, ft_close, fdf);
}
