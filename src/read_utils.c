/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:05:25 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/12 09:44:38 by aweissha         ###   ########.fr       */
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
		ft_free_and_error("Error: no permission or file not existing.", fdf);
	i = 1;
	bytes_read = 1;
	while (1)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read == -1)
			ft_free_and_error("Error reading the file", fdf);
		if (bytes_read == 0)
			break ;
		if (buffer[0] == '\n')
			i++;
	}
	if (buffer[0] == '\n')
		i--;
	if (close(fd) == -1)
		ft_free_and_error("Error closing the file", fdf);
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
		ft_free_and_error("Error opening the file", fdf);
	line = get_next_line(fd, 1);
	if (line == NULL)
		ft_free_and_error("Get_next_line failed", fdf);
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
		ft_free_and_error("Error closing the file", fdf);
	return (count);
}

void	ft_get_color(t_dot *dot, char *str)
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
