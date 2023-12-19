/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:29:38 by aweissha          #+#    #+#             */
/*   Updated: 2023/12/19 18:54:11 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_count_lines(char *filename)
{
	int		fd;
	int		i;
	char	buffer[1];
	int		bytes_read;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Error opening the file");
	i = 1;
	bytes_read = 1;		
	while (1)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read == -1)
			ft_error("Error reading the file");
		if (bytes_read == 0)
			break ;
		if (buffer[0] == '\n')
			i++;
	}
	if (close(fd) == -1)
		ft_error("Error closing the file");
	return (i);
}

int	ft_count_width(char *filename)
{
	int		fd;
	int		i;
	int		count;
	char	*line;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Error opening the file");
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
		ft_error("Error closing the file");
	return (count);
}

void	ft_fill_x(t_map *map, int *matrix, char *line)
{
	int	i;
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

void	ft_create_matrix(t_map *map, int fd)
{
	int	i;

	char	*line;

	map->matrix = malloc(sizeof(int *) * map->height);
	if (map->matrix == NULL)
		ft_error("Memory allocation for matrix failed");	
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		(map->matrix)[i] = malloc(sizeof(int) * map->width);
		if ((map->matrix)[i] == NULL)
			ft_error("Memory allocation for matrix failed (2)");
		ft_fill_x(map, (map->matrix)[i], line);
		free(line);
		i++;
	}

}

void	ft_fill_map(t_map *map)
{
	int	fd;

	map->height = ft_count_lines("42.fdf");
	map->width = ft_count_width("42.fdf");
	fd = open("42.fdf", O_RDONLY);
	if (fd == -1)
		ft_error("Error opening the file");
	ft_create_matrix(map, fd);
	if (close(fd) == -1)
		ft_error("Error closing the file");
}
