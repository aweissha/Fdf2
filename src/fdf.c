/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:35:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/05 17:02:54 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	
	if (argc == 2)
	{
		fdf = ft_create_fdf(argv[1]);
		ft_read_file(fdf, argv[1]);

	// // testing
	// printf("map-height: %d\n", fdf->map->height);
	// printf("map-width: %d\n", fdf->map->width);	
	// int i = 0;
	// while(i < fdf->map->height)
	// {	
	// 	int j = 0;
	// 	while (j < fdf->map->width)
	// 	{
	// 		// printf("x: %f\n", fdf->map->matrix[i][j].x);
	// 		// printf("y: %f\n", fdf->map->matrix[i][j].y);
	// 		printf("%d", (int)fdf->map->matrix[i][j].z);
	// 		if (fdf->map->matrix[i][j].color != 0)
	// 			printf(",%#x", fdf->map->matrix[i][j].color);
	// 		printf(" ");
			
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// exit(0);



		ft_draw_map(fdf);
		ft_hook_control(fdf);
		mlx_loop(fdf->mlx_ptr);
		ft_free_fdf(fdf);
	}
	else
		ft_error("wrong number of arguments");
	return (EXIT_SUCCESS);
}


// ToDo:



// check what if left to be implemented and implement it


// check edge cases and evaluation sheet

// go through the whole code again for understanding...what about endian, bpp and so on... where are they defined?
// check for memory leaks
