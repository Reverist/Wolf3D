/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 15:27:57 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 16:16:54 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	time(t_frame *frame, t_wolf *w)
{
	frame->old_time = frame->time;
	frame->time = SDL_GetTicks();
	frame->frame_time = (frame->time - frame->old_time) / 1000.0;
	frame->move_speed = frame->frame_time * 5.0;
	frame->rot_speed = frame->frame_time * 3.0;
	move(w);
}

void	calc(t_ray *r, t_floor *f)
{
	if (r->side == 0 && r->direction.x > 0)
	{
		f->floor.x = r->ray_position.x;
		f->floor.y = r->ray_position.y + r->wallhit;
	}
	else if (r->side == 2 && r->direction.x < 0)
	{
		f->floor.x = r->ray_position.x + 1.0;
		f->floor.y = r->ray_position.y + r->wallhit;
	}
	else if (r->side == 1 && r->direction.y > 0)
	{
		f->floor.x = r->ray_position.x + r->wallhit;
		f->floor.y = r->ray_position.y;
	}
	else
	{
		f->floor.x = r->ray_position.x + r->wallhit;
		f->floor.y = r->ray_position.y + 1.0;
	}
}

void	cast_floor(t_ray *r, t_floor *f, t_wolf *w, int x)
{
	int	y;

	f->player_dist = 0.0;
	calc(r, f);
	if (r->draw.y < 0)
		r->draw.y = WIN_H;
	y = r->draw.y;
	while (++y < WIN_H)
	{
		f->dist = WIN_H / (2.0 * y - WIN_H);
		f->w = (f->dist - f->player_dist) / (r->walldist - f->player_dist);
		f->curr.x = f->w * f->floor.x + (1.0 - f->w) * w->player.pos.x;
		f->curr.y = f->w * f->floor.y + (1.0 - f->w) * w->player.pos.y;
		f->ftext.x = (int)(f->curr.x * TEXT_WIDTH) % TEXT_WIDTH;
		f->ftext.y = (int)(f->curr.y * TEXT_HEIGHT) % TEXT_HEIGHT;
		r->color = w->texture[5][TEXT_HEIGHT * f->ftext.y +
			f->ftext.x];
		pixel_put(&w->sdl.img, x, y, r->color);
		r->color = w->texture[6][TEXT_HEIGHT * f->ftext.y +
			f->ftext.x];
		pixel_put(&w->sdl.img, x, WIN_H - y, r->color);
	}
}

int		set_color(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	ray_cast(t_wolf *w)
{
	int		x;
	t_ray	ray;
	t_floor	f;

	x = -1;
	while (++x < (int)w->sdl.img.width)
	{
		ray.cam_x = 2 * x / (double)w->sdl.img.width - 1;
		ray.direction.x = w->player.dir.x + w->player.cam.x * ray.cam_x;
		ray.direction.y = w->player.dir.y + w->player.cam.y * ray.cam_x;
		ray.ray_position.x = (int)w->player.pos.x;
		ray.ray_position.y = (int)w->player.pos.y;
		ray.raydelta.x = fabs(1 / ray.direction.x);
		ray.raydelta.y = fabs(1 / ray.direction.y);
		ray.hit = 0;
		setup_ray_dir(&ray, w);
		dda(&ray, w);
		walldist(&ray, w);
		wall_height(&ray, w);
		draw_text(&ray, w, x);
		cast_floor(&ray, &f, w, x);
	}
}
