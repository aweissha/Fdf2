/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:35:49 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/29 14:49:40 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->mlx_window = NULL;
	fdf->mlx_img = NULL;
	fdf->map = NULL;
	fdf->data_addr = NULL;
	fdf->zoom = 20;
	fdf->shift_x = 350;
	fdf->shift_y = 350;
	fdf->x_angle = 0;
	fdf->y_angle = 0;
	fdf->z_angle = 0;
	fdf->z_scale = 1;
	fdf->isometric = 1;
}

void	ft_init_dot(t_dot *dot)
{
	dot->x = 0;
	dot->y = 0;
	dot->z = 0;
	dot->color = 0x000000;
}

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while(i < map->height)
	{
		free((map->matrix)[i]);
		i++;
	}
	free(map->matrix);
}

void	ft_free_fdf(t_fdf *fdf)
{

	if (fdf->mlx_img != NULL)
		mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_img);
	if (fdf->mlx_window != NULL)		
		mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
	if (fdf->map != NULL)
		ft_free_map(fdf->map);	
	if (fdf->mlx_ptr != NULL)
		free(fdf->mlx_ptr);
	free(fdf);
}

void	ft_put_pixel(t_fdf *fdf, float x, float y, int color)
{
	int	i;
	
	i = ((int)y * fdf->size_line) + ((int)x * (fdf->bpp / 8));
	*(unsigned int *)(fdf->data_addr + i) = color;
}

void	ft_handle_arrows(int keycode, t_fdf *fdf)
{
	if (keycode == ARROW_UP)
		fdf->shift_y -= 10;
	if (keycode == ARROW_DOWN)
		fdf->shift_y += 10;
	if (keycode == ARROW_RIGHT)
		fdf->shift_x += 10;
	if (keycode == ARROW_LEFT)
		fdf->shift_x -= 10;
}

void	ft_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS)
		fdf->zoom += 10;
	if (keycode == MINUS && fdf->zoom >= 10)
		fdf->zoom -= 10;
}

void	ft_replace_img(t_fdf *fdf)
{
	if (fdf->mlx_img != NULL)
		mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_img);
	fdf->mlx_img = NULL;
	fdf->data_addr = NULL;
	fdf->mlx_img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (fdf->mlx_img == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("initializing image failed");
	}
	fdf->data_addr = mlx_get_data_addr(fdf->mlx_img, &fdf->bpp, &fdf->size_line, &fdf->endian);
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
		fdf->z_scale += 0.1;
	else if (keycode == K)
		fdf->z_scale -= 0.1;
}


int ft_key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		ft_free_fdf(fdf);
		exit(0);
	}
	// Here, rotations zoom and so on will be implemented.
	else if (keycode == ARROW_UP || keycode == ARROW_DOWN || keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
		ft_handle_arrows(keycode, fdf);
	else if (keycode == PLUS || keycode == MINUS)
		ft_zoom(keycode, fdf);
	else if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == X || keycode == C)
		ft_rotate(keycode, fdf);
	else if (keycode == J || keycode == K)
		ft_scale_z(keycode, fdf);
		
	// vielleicht noch space und R beruecksichtigen
	else
	{
		ft_printf("The %d key has been pressed\n", keycode);
		return (0);
	}
	ft_replace_img(fdf);
	ft_draw_map(fdf);
	return (0);
}

t_map	*ft_init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map *));
	if (map == NULL)
	{
		ft_error("memory allocation creating the map struct failed");
		return (NULL);
	}
	map->height = 0;
	map->width = 0;
	map->matrix = NULL;
	return (map);
}

void	ft_hook_controls(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_window, 2, 0, ft_key_hook, fdf);
}

int	main(void)
{
	t_fdf	*fdf;
	t_map	*map;

	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		ft_error("allocation of memory for t_fdf failed");
	ft_init_fdf(fdf);
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("mlx connection failed");		
	}
	fdf->mlx_window = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "Fdf");
	if (fdf->mlx_window == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("window creation failed");
	}
	// create new image
	fdf->mlx_img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (fdf->mlx_img == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("initializing image failed");
	}
	// put the pointer to the pixel buffer of the image to the struct fdf
	fdf->data_addr = mlx_get_data_addr(fdf->mlx_img, &fdf->bpp, &fdf->size_line, &fdf->endian);

	// read the file and safe the data in the map struct
	map = ft_init_map();
	if (map == NULL)
		ft_free_fdf(fdf);
	fdf->map = map;
	ft_fill_map(map, fdf);
	ft_draw_map(fdf);

	// testing
	// printf("map-height: %d\n", map->height);
	// printf("map-width: %d\n", map->width);	
	// int i = 0;
	// while(i < map->height)
	// {	
	// 	int j = 0;
	// 	while (j < map->width)
	// 	{
	// 		if (map->matrix[i][j] == 0)
	// 			printf("  %d", map->matrix[i][j]);
	// 		else if (map->matrix[i][j] == 10)
	// 			printf(" %d", map->matrix[i][j]);
	// 		j++;			
	// 	}
	// 	printf("\n");
	// 	i++;
	// }


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
	ft_hook_controls(fdf);
	// mlx_key_hook(fdf->mlx_window, ft_key_hook, fdf);


	
	mlx_loop(fdf->mlx_ptr);
	
	
	

	ft_free_fdf(fdf);

	// check for memory leaks !! maybe u have to free all kind of things that was malloced before...

	return (EXIT_SUCCESS);
}
