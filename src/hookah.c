/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookah.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 15:33:15 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 15:48:28 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	move(t_wolf *w)
{
	if (w->keys.key1 == MOVE_FORWARD)
	{
		if (w->map.map_arr[(int)(w->player.pos.x + w->player.dir.x *
					w->frame.move_speed)][(int)w->player.pos.y] == 0)
			w->player.pos.x += w->player.dir.x * w->frame.move_speed;
		if (w->map.map_arr[(int)w->player.pos.x][(int)(w->player.pos.y +
					w->player.dir.y * w->frame.move_speed)] == 0)
			w->player.pos.y += w->player.dir.y * w->frame.move_speed;
	}
	if (w->keys.key1 == MOVE_BACKWARD)
	{
		if (w->map.map_arr[(int)(w->player.pos.x - w->player.dir.x *
					w->frame.move_speed)][(int)w->player.pos.y] == 0)
			w->player.pos.x -= w->player.dir.x * w->frame.move_speed;
		if (w->map.map_arr[(int)w->player.pos.x][(int)(w->player.pos.y -
					w->player.dir.y * w->frame.move_speed)] == 0)
			w->player.pos.y -= w->player.dir.y * w->frame.move_speed;
	}
	if (w->keys.key2 == TURN_RIGHT || w->keys.key2 == TURN_LEFT)
		turning_right(w);
}

void	turning_right(t_wolf *w)
{
	if (w->keys.key2 == TURN_RIGHT)
	{
		w->olddir = w->player.dir.x;
		w->player.dir.x = w->player.dir.x * cos(-w->frame.rot_speed) -
			w->player.dir.y * sin(-w->frame.rot_speed);
		w->player.dir.y = w->olddir * sin(-w->frame.rot_speed) +
			w->player.dir.y * cos(-w->frame.rot_speed);
		w->oldplane = w->player.cam.x;
		w->player.cam.x = w->player.cam.x * cos(-w->frame.rot_speed) -
			w->player.cam.y * sin(-w->frame.rot_speed);
		w->player.cam.y = w->oldplane * sin(-w->frame.rot_speed) +
			w->player.cam.y * cos(-w->frame.rot_speed);
	}
	if (w->keys.key2 == TURN_LEFT)
		turning_left(w);
}

void	key_down(int key, t_wolf *w)
{
	if (key == SDLK_ESCAPE)
		w->sdl.running = 0;
	else if (key == SDLK_UP || key == SDLK_w)
		w->keys.key1 = MOVE_FORWARD;
	else if (key == SDLK_DOWN || key == SDLK_s)
		w->keys.key1 = MOVE_BACKWARD;
	else if (key == SDLK_RIGHT || key == SDLK_d)
		w->keys.key2 = TURN_RIGHT;
	else if (key == SDLK_LEFT || key == SDLK_a)
		w->keys.key2 = TURN_LEFT;
}

void	key_up(int key, t_wolf *w)
{
	if (key == SDLK_UP || key == SDLK_w)
		w->keys.key1 = 0;
	else if (key == SDLK_DOWN || key == SDLK_s)
		w->keys.key1 = 0;
	else if (key == SDLK_RIGHT || key == SDLK_d)
		w->keys.key2 = 0;
	else if (key == SDLK_LEFT || key == SDLK_a)
		w->keys.key2 = 0;
}

void	sdl_hook(t_wolf *w)
{
	while (SDL_PollEvent(&w->sdl.e) != 0)
	{
		if (w->sdl.e.type == SDL_QUIT)
			w->sdl.running = 0;
		else if (w->sdl.e.type == SDL_KEYDOWN)
			key_down(w->sdl.e.key.keysym.sym, w);
		else if (w->sdl.e.type == SDL_KEYUP)
			key_up(w->sdl.e.key.keysym.sym, w);
	}
}
