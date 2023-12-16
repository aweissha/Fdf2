/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:35:49 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/16 19:08:25 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define WIDTH 1024
#define HEIGHT 1024

void ft_free_fdf(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
	free(fdf->mlx_ptr);
	free(fdf);
}

int ft_key_hook(int keysym, t_fdf *fdf)
{
	if (keysym == 53)
	{
		ft_free_fdf(fdf);
		exit(0);
	}
	// Here, rotations zoom and so on will be implemented.
	else
	{
		ft_printf("The %d key has been pressed\n", keysym);
		return (0);	
	}
	return (0);
}

int	main(void)
{
	t_fdf	*fdf;
	// int		x;
	// int		y;
	
	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		ft_error("allocation of memory for t_fdf failed");
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("mlx connection failed");		
	}

	fdf->mlx_window = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "Fdf");
	if (fdf->mlx_window == NULL)
	{
		ft_free(fdf);
		//maybe additional frees of memory associated with mlx_ptr?
		ft_error("window creation failed");
	}

	// create new image
	fdf->mlx_img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (fdf->mlx_img == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("initializing image failed");
	}
	mlx_get_data_addr(fdf->mlx_img, 32, &fdf->mlx_img->width, )

	
	// y = WIDTH * 0.2;
	// while (y < WIDTH * 0.8)
	// {
	// 	x = HEIGHT * 0.2;
	// 	while (x < HEIGHT * 0.8)
	// 	{
	// 		mlx_pixel_put(fdf->mlx_ptr, fdf->mlx_window, x, y, 0x00ff00);
	// 		x++;	
	// 	}
	// 	y++;
	// }
	// mlx_string_put(fdf->mlx_ptr, fdf->mlx_window, 850, 970, 0x009999, "@aweissha-studios");
	
	// HOOKS
	mlx_key_hook(fdf->mlx_window, ft_key_hook, fdf);


	
	mlx_loop(fdf->mlx_ptr);
	
	
	

	



	// mlx_destroy_image(mlx_ptr, mlx_img_list_t *img_todel);
	// if there is no function to destroy the mlx_ptr, i guess i just free mlx_ptr. Maybe I need to free some additional stuff associated with mlx_ptr however...
	ft_free_fdf(fdf);

	// check for memory leaks !! maybe u have to free all kind of things that was malloced before...

	return (EXIT_SUCCESS);
}
