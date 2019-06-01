/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:04:47 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 16:05:19 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	texture_free(t_wolf *w)
{
	int i;

	i = -1;
	while (++i < 8)
		free(w->texture[i]);
}

void	end(t_wolf *w)
{
	free(w->sdl.img.pixels);
	SDL_DestroyTexture(w->sdl.texture);
	SDL_DestroyTexture(w->inface.hood);
	SDL_DestroyRenderer(w->sdl.ren);
}
