/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:13:34 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 17:55:13 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int		get_color(void *ptr, int i)
{
	unsigned char *tmp;

	tmp = (unsigned char*)ptr;
	return (set_color(tmp[i + 2], tmp[i + 1], tmp[i]));
}

void	get_pic(int *pixels, const char *path)
{
	SDL_Surface		*sur;
	int				i;
	int				size;
	int				k;

	i = -1;
	size = TEXT_HEIGHT * TEXT_WIDTH;
	k = 0;
	if (!(sur = IMG_Load(path)))
		error("put the files back");
	while (++i < size)
	{
		pixels[i] = get_color(sur->pixels, k);
		k += 4;
	}
	SDL_FreeSurface(sur);
}

void	fill_texture_custom(t_wolf *w)
{
	get_pic(w->texture[0], "./pics/eagle.png");
	get_pic(w->texture[1], "./pics/redbrick.png");
	get_pic(w->texture[2], "./pics/bluestone.png");
	get_pic(w->texture[3], "./pics/wood.png");
	get_pic(w->texture[4], "./pics/greystone.png");
	get_pic(w->texture[5], "./pics/mossy.png");
	get_pic(w->texture[6], "./pics/colorstone.png");
	get_pic(w->texture[7], "./pics/purplestone.png");
}

void	init_text(t_wolf *w)
{
	int	i;

	i = -1;
	while (++i < 8)
		w->texture[i] = (int*)malloc(sizeof(int) *
				(int)TEXT_HEIGHT * (int)TEXT_WIDTH);
	fill_texture_custom(w);
}
