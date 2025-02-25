/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:35:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 14:37:44 by aweissha         ###   ########.fr       */
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
		ft_set_zoom(fdf);
		ft_draw_map(fdf);
		ft_hook_control(fdf);
		mlx_loop(fdf->mlx_ptr);
		ft_free_fdf(fdf);
	}
	else
		ft_error("wrong number of arguments");
	return (EXIT_SUCCESS);
}
