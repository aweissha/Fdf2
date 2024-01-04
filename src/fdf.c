/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:35:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/04 10:31:12 by aweissha         ###   ########.fr       */
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
// fix the count width function for counting correctly when colors --check

// change file reading algorithm to a 2dim array of t_dots




// make the other maps work
// implement colors
// check what if left to be implemented and implement it
// check edge cases and evaluation sheet
// implement, that the figure cant leave the image and avoid any segmentation faults by setting limits using if statements
// change variable names in the rotation functions
// go through the whole code again for understanding...what about endian, bpp and so on... where are they defined?
// check for memory leaks
// remove ternary and change the rotational functions
