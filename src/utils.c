/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:56 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/12 10:07:31 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

float	max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ft_set_zoom(t_fdf *fdf)
{
	fdf->zoom = min(WIDTH / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
}
