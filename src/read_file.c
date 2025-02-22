/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:29:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 13:45:52 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_fill_map(t_fdf *fdf, t_map *map, t_dot *matrix, char *line)
{
	int		i;
	char	**array;

	array = ft_split(line, ' ');
	if (array == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("Memory allocation for matrix failed");
	}
	i = 0;
	while (i < map->width)
	{
		ft_init_dot(&matrix[i]);
		matrix[i].z = ft_atoi(array[i]);
		ft_get_color(&matrix[i], array[i]);
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_read_lines(t_map *map, int fd, t_fdf *fdf)
{
	int		i;
	char	*line;

	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd, 0);
		if (line == NULL)
		{
			ft_free_fdf(fdf);
			ft_error("Get_next_line failed");
		}
		(map->matrix)[i] = malloc(sizeof(t_dot) * (map->width));
		if ((map->matrix)[i] == NULL)
		{
			ft_free_fdf(fdf);
			ft_error("Memory allocation for matrix failed (2)");
		}
		ft_fill_map(fdf, map, (map->matrix)[i], line);
		free(line);
		i++;
	}
	(map->matrix)[i] = NULL;
}

void	ft_fill_dots(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->matrix[i][j].y = i;
			map->matrix[i][j].x = j;
			j++;
		}
		i++;
	}
}

void	ft_create_matrix(t_map *map, int fd, t_fdf *fdf)
{
	map->matrix = malloc(sizeof(t_dot *) * (map->height + 1));
	if (map->matrix == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("Memory allocation for matrix failed");
	}
	ft_read_lines(map, fd, fdf);
	ft_fill_dots(map);
}

void	ft_read_file(t_fdf *fdf, char *filename)
{
	int		fd;
	t_map	*map;

	map = fdf->map;
	map->height = ft_count_lines(filename, fdf);
	map->width = ft_count_width(filename, fdf);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_free_fdf(fdf);
		ft_error("Error opening the file.");
	}
	ft_create_matrix(map, fd, fdf);
	if (close(fd) == -1)
	{
		ft_free_fdf(fdf);
		ft_error("Error closing the file");
	}
}
