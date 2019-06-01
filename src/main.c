/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:16:48 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 17:54:58 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

void	init_wolf(t_wolf *w)
{
	t_point param;

	w->player.pos = w->map.init_player;
	w->player.dir = (t_matrix){-1, 0};
	w->player.cam = (t_matrix){0, 0.66};
	w->inface.hood = IMG_LoadTexture(w->sdl.ren, "./pics/hood.png");
	SDL_QueryTexture(w->inface.hood, NULL, NULL, &param.x, &param.y);
	w->inface.texture.x = 0;
	w->inface.texture.y = WIN_H - param.y;
	w->inface.texture.w = WIN_W;
	w->inface.texture.h = param.y;
	SDL_RenderCopy(w->sdl.ren, w->inface.hood, NULL, &w->inface.texture);
	mus(w);
}

void	mallocd(t_map *map)
{
	int i;

	i = -1;
	if (!(map->map_arr = (int**)malloc(sizeof(int*) * map->map_height)))
		error("Memory allocation error");
	while (++i < map->map_height)
	{
		if (!(map->map_arr[i] = (int*)malloc(sizeof(int) * map->map_width)))
			error("Memory allocation error");
	}
}

void	mus(t_wolf *w)
{
	Mix_OpenAudio(44100, AUDIO_S16SYS,
			2, 1500);
	if (!(w->sound = Mix_LoadWAV("gost.mp3")))
		error("Please don't stop the music");
	Mix_PlayChannel(-1, w->sound, 0);
}

int		main(int ac, char **av)
{
	t_wolf	w;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (ac == 2)
		read_dimension(fd, &w.map);
	else
		error("Usage : ./wolf3d [mapname]");
	mallocd(&w.map);
	parse_map(fd, &w.map);
	init_sdl(&w.sdl, "wolf");
	init_wolf(&w);
	while (w.sdl.running)
	{
		init_text(&w);
		sdl_hook(&w);
		ray_cast(&w);
		image_put(&w.sdl);
		SDL_RenderCopy(w.sdl.ren, w.inface.hood, NULL, &w.inface.texture);
		SDL_RenderPresent(w.sdl.ren);
		time(&w.frame, &w);
		texture_free(&w);
	}
	end(&w);
	return (0);
}
