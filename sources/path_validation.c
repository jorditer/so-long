/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordi <jordi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:41:40 by jordi             #+#    #+#             */
/*   Updated: 2025/02/14 17:02:19 by jordi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int x, int y, int *collect_count)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		(*collect_count)--;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, collect_count);
	flood_fill(map, x - 1, y, collect_count);
	flood_fill(map, x, y + 1, collect_count);
	flood_fill(map, x, y - 1, collect_count);
}

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;
	
	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = malloc(sizeof(char) * (map->width + 1));
		if (!copy[i])
			return (NULL);
		ft_memset(copy[i], 0, map->width + 1);
		i++;
	}
	copy[i] = NULL;
	i = -1;
	while (++i < map->height)
		for (int j = 0; j < map->width; j++)
			copy[i][j] = map->grid[i][j];
	return (copy);
}

static void free_copy(char **copy, int height)
{
	int i;
	
	i = 0;
	while (i < height)
		free(copy[i++]);
	free(copy);
}

void    check_path(t_map *map)
{
	char    **copy;
	int     collect_count;
	int     i;
	int     exit_found;
	
	copy = copy_map(map);
	if (!copy)
		exit(EXIT_FAILURE);
	collect_count = map->collect_count;
	flood_fill(copy, map->player_x, map->player_y, &collect_count);
	exit_found = 0;
	i = -1;
	while (++i < map->height && !exit_found)
		for (int j = 0; j < map->width && !exit_found; j++)
			if (map->grid[i][j] == 'E' && copy[i][j] == 'F')
				exit_found = 1;
	free_copy(copy, map->height);
	if (!exit_found || collect_count > 0)
	{
		write(2, "Error\nNo valid path found\n", 25);
		exit(EXIT_FAILURE);
	}
}

t_map   *validate_map(char *file)
{
	t_map   *map;
	
	check_extension(file);
	map = malloc(sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	get_map_size(map, file);
	read_map(map, file);
	check_walls(map);
	check_components(map);
	check_path(map);
	return (map);
}