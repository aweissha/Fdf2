/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:29:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/04 10:31:22 by aweissha         ###   ########.fr       */
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
		ft_free_fdf(fdf);		
		ft_error("Error opening the file");		
	}
	i = 1;
	bytes_read = 1;		
	while (1)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read == -1)
		{
			ft_free_fdf(fdf);				
			ft_error("Error reading the file");
		}
		if (bytes_read == 0)
			break ;
		if (buffer[0] == '\n')
			i++;
	}
	if (close(fd) == -1)
	{
		ft_free_fdf(fdf);		
		ft_error("Error closing the file");		
	}
	return (i - 1);
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
		ft_free_fdf(fdf);			
		ft_error("Error opening the file");
	}
	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_free_fdf(fdf);			
		ft_error("Get_next_line failed");
	}
	i = 0;
	count = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\n'))
			count++;
		i++;
	}
	free(line);
	if (close(fd) == -1)
	{
		ft_free_fdf(fdf);	
		ft_error("Error closing the file");		
	}
	return (count);
}

void	ft_fill_map(t_fdf *fdf, t_map *map, int *matrix, char *line)
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
		matrix[i] = ft_atoi(array[i]);
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
		line = get_next_line(fd);
		if (line == NULL)
		{
			ft_free_fdf(fdf);			
			ft_error("Get_next_line failed");
		}
		(map->matrix)[i] = malloc(sizeof(int) * (map->width));
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

void	ft_create_matrix(t_map *map, int fd, t_fdf *fdf)
{
	map->matrix = malloc(sizeof(int *) * (map->height + 1));
	if (map->matrix == NULL)
	{
		ft_free_fdf(fdf);
		ft_error("Memory allocation for matrix failed");
	}
	ft_read_lines(map, fd, fdf);
}

void	ft_read_file(t_fdf *fdf, char *filename)
{
	int	fd;
	t_map *map = fdf->map;

	map->height = ft_count_lines(filename, fdf);
	map->width = ft_count_width(filename, fdf);
	
	//testing
	// printf("height: %d\n", map->height);
	// printf("width: %d\n", map->width);
	// exit(0);
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_free_fdf(fdf);		
		ft_error("Error opening the file");		
	}
	ft_create_matrix(map, fd, fdf);
	if (close(fd) == -1)
	{
		ft_free_fdf(fdf);
		ft_error("Error closing the file");
	}
}
