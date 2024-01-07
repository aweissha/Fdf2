/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:29:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/07 19:13:53 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	is_in_base(int base, char c)
{
	int		i;
	char	base_str[] = "0123456789ABCDEF";
	char	base_str2[] = "0123456789abcdef";
	
	i = 0;
	while (i < base)
	{
		if (c == base_str[i] || c == base_str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	minus_counter;
	int	number;

	i = 0;
	minus_counter = 1;
	
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus_counter = minus_counter * (-1);
		i++;
	}
	while (is_in_base(str_base, str[i]) == 1
		&& str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			number = number * str_base + str[i] - 48;
		else if (str[i] >= 'A' && str[i] <= 'F')
			number = number * str_base + str[i] - 65 + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			number = number * str_base + str[i] - 97 + 10;
		i++;
	}
	return (number * minus_counter);
}

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
	if (buffer[0] == '\n')
		i--;
	if (close(fd) == -1)
	{
		ft_free_fdf(fdf);		
		ft_error("Error closing the file");		
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
		ft_free_fdf(fdf);			
		ft_error("Error opening the file");
	}
	line = get_next_line(fd, 1);
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

static void	ft_get_color(t_dot *dot, char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
		{
			dot->color = ft_atoi_base(&str[i + 3], 16);
			break ;
		}
		i++;
	}
}

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

static void	ft_fill_dots(t_map *map)
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
	int	fd;
	t_map *map = fdf->map;

	map->height = ft_count_lines(filename, fdf);
	map->width = ft_count_width(filename, fdf);
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
