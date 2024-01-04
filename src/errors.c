/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:04:24 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/03 10:17:15 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_error(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
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
