/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:29:38 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/26 11:21:54 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_count_lines(char *filename, t_fdf *fdf)
{
	int		fd;
	int		i;
	char	buffer[1];
	int		bytes_read;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error("Error opening the file");		
		ft_free_fdf(fdf);
	}
	i = 1;
	bytes_read = 1;		
	while (1)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read == -1)
		{
			ft_error("Error reading the file");
			ft_free_fdf(fdf);		
		}
		if (bytes_read == 0)
			break ;
		if (buffer[0] == '\n')
			i++;
	}
	if (close(fd) == -1)
	{
		ft_error("Error closing the file");		
		ft_free_fdf(fdf);
	}
	return (i);
}

int	ft_count_width(char *filename, t_fdf *fdf)
{
	int		fd;
	int		i;
	int		count;
	char	*line;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error("Error opening the file");
		ft_free_fdf(fdf);	
	}
	line = get_next_line(fd);	
	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if ((ft_isdigit(line[i]) == 1) && (ft_isdigit(line[i + 1]) == 0))
			count++;
		i++;
	}
	free(line);
	if (close(fd) == -1)
	{
		ft_error("Error closing the file");		
		ft_free_fdf(fdf);
	}
	return (count);
}

void	ft_fill_x(t_map *map, int *matrix, char *line)
{
	int		i;
	char	**array;

	array = ft_split(line, ' ');
	i = 0;
	while (i < map->width)
	{
		matrix[i] = ft_atoi(array[i]);
		free(array[i]);		
		i++;
	}
	free(array);
}

void	ft_create_matrix(t_map *map, int fd, t_fdf *fdf)
{
	int		i;
	char	*line;

	map->matrix = malloc(sizeof(int *) * (map->height + 1));
	if (map->matrix == NULL)
	{
		ft_error("Memory allocation for matrix failed");
		ft_free_fdf(fdf);
	}
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		(map->matrix)[i] = malloc(sizeof(int) * (map->width));
		if ((map->matrix)[i] == NULL)
		{
			ft_error("Memory allocation for matrix failed (2)");
			ft_free_fdf(fdf);
		}
		ft_fill_x(map, (map->matrix)[i], line);
		free(line);
		i++;
	}
	(map->matrix)[i] = NULL;
}

void	ft_fill_map(t_map *map, t_fdf *fdf)
{
	int	fd;

	map->height = ft_count_lines("42.fdf", fdf);
	map->width = ft_count_width("42.fdf", fdf);
	fd = open("42.fdf", O_RDONLY);
	if (fd == -1)
	{
		ft_error("Error opening the file");		
		ft_free_fdf(fdf);
	}
	ft_create_matrix(map, fd, fdf);
	if (close(fd) == -1)
	{
		ft_free_fdf(fdf);
		ft_error("Error closing the file");
	}
}
