/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:30:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/07 18:16:25 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_close(t_fdf *fdf)
{
	ft_free_fdf(fdf);

	system("leaks fdf");
		
	exit(0);
}

// void	ft_replace_img(t_fdf *fdf)
// {
// 	if (fdf->mlx_img != NULL)
// 		mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_img);
// 	fdf->mlx_img = NULL;
// 	fdf->data_addr = NULL;
// 	fdf->mlx_img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
// 	if (fdf->mlx_img == NULL)
// 	{
// 		ft_free_fdf(fdf);
// 		ft_error("initializing image failed");
// 	}
// 	fdf->data_addr = mlx_get_data_addr(fdf->mlx_img, &fdf->bpp, &fdf->size_line, &fdf->endian);
// }

int ft_key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		ft_close(fdf);
	else if (keycode == ARROW_UP || keycode == ARROW_DOWN || keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
		ft_shift(keycode, fdf);
	else if (keycode == PLUS || keycode == MINUS)
		ft_zoom(keycode, fdf);
	else if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == X || keycode == C)
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
