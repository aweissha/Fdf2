/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:04:24 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 12:04:14 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_error(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	ft_free_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map->height)
	{
		free((fdf->map->matrix)[i]);
		i++;
	}
	if (fdf->map->matrix != NULL)
		free(fdf->map->matrix);
	if (fdf->map != NULL)
		free(fdf->map);
}

void	ft_free_fdf(t_fdf *fdf)
{
	if (fdf->mlx_img != NULL)
		mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_img);
	if (fdf->mlx_window != NULL)
		mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
	if (fdf->map != NULL)
		ft_free_map(fdf);
	if (fdf->mlx_ptr != NULL)
		free(fdf->mlx_ptr);
	free(fdf);
}

void	ft_free_and_error(char *message, t_fdf *fdf)
{
	ft_free_fdf(fdf);
	ft_error(message);
}
