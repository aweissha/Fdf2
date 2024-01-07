/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:56:34 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/07 18:39:25 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_init_dot(t_dot *dot)
{
	dot->x = 0;
	dot->y = 0;
	dot->z = 0;
	dot->color = 0xffffff;
}

void	ft_init_map(t_fdf *fdf)
{
	fdf->map = malloc(sizeof(t_map));
	if (fdf->map == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("memory allocation creating the map struct failed");
	}
	fdf->map->height = 0;
	fdf->map->width = 0;
	fdf->map->matrix = NULL;
}

void	ft_init(t_fdf *fdf, char *filename)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("mlx connection failed");		
	}
	fdf->mlx_window = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, filename);
	if (fdf->mlx_window == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("window creation failed");
	}
	fdf->mlx_img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (fdf->mlx_img == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("initializing image failed");
	}
	fdf->data_addr = mlx_get_data_addr(fdf->mlx_img, &fdf->bpp, &fdf->size_line, &fdf->endian);
	ft_init_map(fdf);
}

void	ft_init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->mlx_window = NULL;
	fdf->mlx_img = NULL;
	fdf->map = NULL;
	fdf->data_addr = NULL;
	fdf->zoom = 20;
	fdf->shift_x = WIDTH / 2;
	fdf->shift_y = HEIGHT / 2;
	fdf->x_angle = -0.458393;
	fdf->y_angle = -0.439823;
	fdf->z_angle = 0.691150;
	fdf->z_scale = 1;
	fdf->isometric = 1;
}

t_fdf	*ft_create_fdf(char *filename)
{
	t_fdf	*fdf;
	
	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		ft_error("allocation of memory for t_fdf failed");
	ft_init_fdf(fdf);
	ft_init(fdf, filename);
	return (fdf);
}
