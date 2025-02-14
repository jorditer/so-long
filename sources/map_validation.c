/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordi <jordi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:31:35 by jordi             #+#    #+#             */
/*   Updated: 2025/02/14 17:53:43 by jordi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if ((i == 0 || i == map->height - 1 || j == 0
					|| j == map->width - 1) && map->grid[i][j] != '1')
			{
				write(2, "Error\nMap is not surrounded by walls\n", 37);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void	check_args(int argc, char **filename)
{
	int	len;

	if (argc != 2)
	{
		write(2, "Error\nInvalid number of argumens\n", 34);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(filename[1]);
	if (len < 5 || ft_strcmp(filename[1] + len - 4, ".ber") != 0)
	{
		write(2, "Error\nInvalid file extension\n", 29);
		exit(EXIT_FAILURE);
	}
}

static void	process_line(t_map *map, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (map->width == 0)
		map->width = line_len;
	else if (line_len != map->width)
	{
		write(2, "Error\nMap is not rectangular\n", 29);
		exit(EXIT_FAILURE);
	}
	map->height++;
}

void	get_map_size(t_map *map, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nCannot open file\n", 23);
		exit(EXIT_FAILURE);
	}
	map->width = 0;
	map->height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	read_map(t_map *map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		exit(EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->grid[i] = line;
		if (map->grid[i][ft_strlen(map->grid[i]) - 1] == '\n')
			map->grid[i][ft_strlen(map->grid[i]) - 1] = '\0';
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	close(fd);
}

static void	count_component(t_map *map, char c, int i, int j)
{
	if (c == 'P')
	{
		map->player_count++;
		map->player_x = j;
		map->player_y = i;
	}
	else if (c == 'C')
		map->collect_count++;
	else if (c == 'E')
		map->exit_count++;
	else if (c != '0' && c != '1')
	{
		write(2, "Error\nInvalid character in map\n", 31);
		exit(EXIT_FAILURE);
	}
}

void	check_components(t_map *map)
{
	int	i;
	int	j;
	
	map->player_count = 0;
	map->collect_count = 0;
	map->exit_count = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			count_component(map, map->grid[i][j], i, j);
	}
	if (map->player_count != 1 || map->exit_count != 1 
		|| map->collect_count < 1)
	{
		write(2, "Error\nInvalid number of components\n", 35);
		exit(EXIT_FAILURE);
	}
}