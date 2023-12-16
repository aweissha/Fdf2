/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:13:26 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/16 18:14:37 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../ft_printf/ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>


typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_img;
}	t_fdf;



void	ft_error(char *message);

#endif