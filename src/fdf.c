/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:35:49 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/19 18:58:18 by aweissha         ###   ########.fr       */
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
	if (fdf->data_addr != NULL)
		free(fdf->data_addr);
	if (fdf->mlx_ptr != NULL)
		free(fdf->mlx_ptr);
	free(fdf);
}

void	ft_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	i;
	
	i = (y * fdf->size_line) + (x * (fdf->bpp / 8));
	*(unsigned int *)(fdf->data_addr + i) = color;
}

void	ft_handle_arrows(int keycode, t_fdf *fdf)
{
	if (keycode == ARROW_UP || keycode == ARROW_DOWN || keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
		ft_put_pixel(fdf, 500, 500, 0xff0000);
}

void	ft_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS || keycode == MINUS)
			ft_put_pixel(fdf, 500, 500, 0x00ff00);
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
	// vielleicht noch space und R beruecksichtigen
	else
	{
		ft_printf("The %d key has been pressed\n", keycode);
		return (0);
	}



	// put the buffered image to the window to make it show up on the screen
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->mlx_img, 0, 0);
	return (0);
}

t_map	*ft_init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map *));
	if (map == NULL)
		ft_error("memory allocation creating the map struct failed");
	map->height = 0;
	map->width = 0;
	map->matrix = NULL;
	return (map);
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
	// put the pointer to the pixel buffer of the image to the struct fdf
	fdf->data_addr = mlx_get_data_addr(fdf->mlx_img, &fdf->bpp, &fdf->size_line, &fdf->endian);



	// read the file and safe the data in the map struct
	map = ft_init_map();
	fdf->map = map;
	ft_fill_map(map);



	// testing
	printf("map-height: %d\n", map->height);
	printf("map-width: %d\n", map->width);	
	int i = 0;
	while(i < map->height)
	{	
		int j = 0;
		while (j < map->width)
		{
			if (map->matrix[i][j] == 0)
				printf("  %d", map->matrix[i][j]);
			else if (map->matrix[i][j] == 10)
				printf(" %d", map->matrix[i][j]);
			j++;			
		}
		printf("\n");
		i++;
	}


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
	// mlx_key_hook(fdf->mlx_window, ft_key_hook, fdf);


	
	// mlx_loop(fdf->mlx_ptr);
	
	
	

	



	// mlx_destroy_image(mlx_ptr, mlx_img_list_t *img_todel);
	// if there is no function to destroy the mlx_ptr, i guess i just free mlx_ptr. Maybe I need to free some additional stuff associated with mlx_ptr however...
	ft_free_fdf(fdf);

	// check for memory leaks !! maybe u have to free all kind of things that was malloced before...

	return (EXIT_SUCCESS);
}
