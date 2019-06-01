/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:17:01 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 17:55:48 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	read_dimension(int fd, t_map *map)
{
	char	**split;
	char	*line;
	int		i;

	i = 0;
	while (i++ < 2)
	{
		if (get_next_line(fd, &line) < 0)
			error("Can't read file");
		split = ft_strsplit(line, ' ');
		free(line);
		if (!split || !*split)
			error("Make as it was.");
		if (!ft_strcmp("WIDTH", split[0]))
			map->map_width = ft_atoi(split[1]);
		if (!ft_strcmp("HEIGHT", split[0]))
			map->map_height = ft_atoi(split[1]);
		free(split[0]);
		free(split[1]);
		free(split);
	}
	if (map->map_height < 3 || map->map_width < 3)
		error("Invalid map");
}

void	init_player(t_map *map, int height, int width)
{
	map->init_player.x = height - 0.5 + 1;
	map->init_player.y = width - 0.5 + 1;
}

void	parse_line(int *arr, char *line, t_map *map, int height)
{
	int		x;
	char	**split;

	x = -1;
	split = ft_strsplit(line, ' ');
	while (split[++x])
	{
		if (x > map->map_width || height > map->map_height - 1)
			error("Wrong map");
		if (!ft_strcmp(split[x], "X"))
			init_player(map, height, x);
		arr[x] = ft_atoi(split[x]);
		free(split[x]);
		if (arr[x] < 0 || (height == 0 && arr[x] == 0) ||
				(height == map->map_height - 1 && arr[x] == 0) ||
		(x == 0 && arr[x] == 0) || (x == map->map_width - 1 && arr[x] == 0))
			error("Wrong borders");
	}
	free(split);
	if (x != map->map_width)
		error("Invalid map.Width");
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	int		red;
	int		height;

	height = 0;
	while ((red = get_next_line(fd, &line)))
	{
		if (red == -1)
			error("Reading file error");
		parse_line(map->map_arr[height], line, map, height);
		free(line);
		height++;
		if (height > map->map_height)
			error("Invalid map.Height[1]");
	}
	if (!map->init_player.x && !map->init_player.y)
		error("No player");
	if (height != map->map_height)
		error("Invalid map. Height");
}

void	turning_left(t_wolf *w)
{
	if (w->keys.key2 == TURN_LEFT)
	{
		w->olddir = w->player.dir.x;
		w->player.dir.x = w->player.dir.x * cos(w->frame.rot_speed) -
			w->player.dir.y * sin(w->frame.rot_speed);
		w->player.dir.y = w->olddir * sin(w->frame.rot_speed) +
			w->player.dir.y * cos(w->frame.rot_speed);
		w->oldplane = w->player.cam.x;
		w->player.cam.x = w->player.cam.x * cos(w->frame.rot_speed) -
			w->player.cam.y * sin(w->frame.rot_speed);
		w->player.cam.y = w->oldplane * sin(w->frame.rot_speed) +
			w->player.cam.y * cos(w->frame.rot_speed);
	}
}
