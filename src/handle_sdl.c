/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:16:39 by akrivosh          #+#    #+#             */
/*   Updated: 2019/05/31 18:16:43 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void				init_sdl(t_sdl *sdl, char *title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		error("SDL_GetError()");
	if (!(sdl->win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WIN_W,
					WIN_H, SDL_WINDOW_SHOWN)))
		error("SDL_GetError()");
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("SDL_GetError()");
	if (!(sdl->texture = SDL_CreateTexture(sdl->ren,
					SDL_PIXELFORMAT_ARGB8888,
					SDL_TEXTUREACCESS_STREAMING,
					WIN_W, WIN_H)))
		error("SDL_GetError()");
	SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 0xFF);
	SDL_RenderClear(sdl->ren);
	SDL_RenderPresent(sdl->ren);
	sdl->img = create_image(WIN_W, WIN_H);
	sdl->running = 1;
}

t_img				create_image(size_t width, size_t height)
{
	t_img img;

	img.width = width;
	img.height = height;
	if (!(img.pixels = ft_memalloc(sizeof(int) * img.width * img.height)))
		error("Memory allocation fault");
	clear_image(&img);
	return (img);
}

void				clear_image(t_img *img)
{
	ft_bzero(img->pixels, img->width * img->height * 4);
}

void				image_put(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, sdl->img.pixels, WIN_W * 4);
	clear_image(&sdl->img);
	SDL_RenderCopy(sdl->ren, sdl->texture, NULL, NULL);
}

void				pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || x > (int)img->width || y < 0 || y > (int)img->height)
		return ;
	img->pixels[x + y * img->width] = color;
}
