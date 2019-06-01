/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:17:22 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 16:13:24 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	setup_ray_dir(t_ray *r, t_wolf *w)
{
	if (r->direction.x < 0)
	{
		r->step.x = -1;
		r->rayside.x = (w->player.pos.x -
				r->ray_position.x) * r->raydelta.x;
	}
	else
	{
		r->step.x = 1;
		r->rayside.x = (r->ray_position.x + 1 -
				w->player.pos.x) * r->raydelta.x;
	}
	if (r->direction.y < 0)
	{
		r->step.y = -1;
		r->rayside.y = (w->player.pos.y -
				r->ray_position.y) * r->raydelta.y;
	}
	else
	{
		r->step.y = 1;
		r->rayside.y = (r->ray_position.y + 1 -
				w->player.pos.y) * r->raydelta.y;
	}
}

void	dda(t_ray *r, t_wolf *w)
{
	while (r->hit == 0)
	{
		if (r->rayside.x < r->rayside.y)
		{
			r->rayside.x += r->raydelta.x;
			r->ray_position.x += r->step.x;
			if (r->direction.x > 0)
				r->side = 0;
			else
				r->side = 2;
		}
		else
		{
			r->rayside.y += r->raydelta.y;
			r->ray_position.y += r->step.y;
			if (r->direction.y > 0)
				r->side = 1;
			else
				r->side = 3;
		}
		if (w->map.map_arr[r->ray_position.x][r->ray_position.y] > 0)
			r->hit = 1;
	}
}

void	draw_text(t_ray *r, t_wolf *w, int x)
{
	int d;
	int y;

	y = r->draw.x - 1;
	r->color = 0;
	while (++y < r->draw.y)
	{
		d = y * 256 - WIN_H * 128 + r->wall_height * 128;
		r->tex.y = ((d * TEXT_HEIGHT) / r->wall_height) / 256;
		if (r->side == 0)
			r->color = w->texture[r->side][TEXT_HEIGHT * r->tex.y + r->tex.x];
		if (r->side == 1)
			r->color = w->texture[r->side][TEXT_HEIGHT * r->tex.y + r->tex.x];
		if (r->side == 2)
			r->color = w->texture[r->side][TEXT_HEIGHT * r->tex.y + r->tex.x];
		if (r->side == 3)
			r->color = w->texture[r->side][TEXT_HEIGHT * r->tex.y + r->tex.x];
		pixel_put(&w->sdl.img, x, y, r->color);
	}
}

void	walldist(t_ray *r, t_wolf *w)
{
	if (r->side == 0 || r->side == 2)
		r->walldist = (r->ray_position.x - w->player.pos.x
				+ (1 - r->step.x) / 2) / r->direction.x;
	else
		r->walldist = (r->ray_position.y - w->player.pos.y
				+ (1 - r->step.y) / 2) / r->direction.y;
}

void	wall_height(t_ray *r, t_wolf *w)
{
	r->wall_height = (int)(w->sdl.img.height / r->walldist);
	r->draw.x = -r->wall_height / 1 + (int)(w->sdl.img.height / 2);
	if (r->draw.x < 0)
		r->draw.x = 0;
	r->draw.y = r->wall_height / 2 + (int)(w->sdl.img.height / 2);
	if (r->draw.y >= WIN_H)
		r->draw.y = WIN_H - 1;
	r->tex_id = w->map.map_arr[r->ray_position.x][r->ray_position.y] - 1;
	if (r->side == 0 || r->side == 2)
		r->wallhit = w->player.pos.y + r->walldist * r->direction.y;
	else
		r->wallhit = w->player.pos.x + r->walldist * r->direction.x;
	r->wallhit -= (int)(r->wallhit);
	r->tex.x = (int)(r->wallhit * TEXT_WIDTH);
}
