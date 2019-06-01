/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrivosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:17:11 by akrivosh          #+#    #+#             */
/*   Updated: 2019/06/01 17:54:25 by akrivosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <fcntl.h>
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# define WIN_W			1280
# define WIN_H			920
# define TEXT_WIDTH			64
# define TEXT_HEIGHT			64
# define MOVE_FORWARD		1
# define MOVE_BACKWARD		2
# define TURN_LEFT			3
# define TURN_RIGHT			4

typedef struct				s_matrix
{
	double x;
	double y;
}							t_matrix;

typedef struct				s_point
{
	int x;
	int y;
}							t_point;

typedef struct				s_img
{
	size_t					width;
	size_t					height;
	unsigned int			*pixels;
}							t_img;

typedef struct				s_player
{
	t_matrix				pos;
	t_matrix				dir;
	t_matrix				cam;
}							t_player;
typedef struct				s_frame
{
	int						time;
	int						old_time;
	double					frame_time;
	double					move_speed;
	double					rot_speed;
}							t_frame;
typedef struct				s_map
{
	t_matrix				init_player;
	int						map_width;
	int						map_height;
	int						**map_arr;
}							t_map;
typedef struct				s_keyboard
{
	int						key1;
	int						key2;
}							t_keyboard;
typedef struct				s_ray
{
	double					cam_x;
	t_matrix				direction;
	double					walldist;
	t_point					ray_position;
	t_matrix				rayside;
	t_matrix				raydelta;
	t_point					step;
	int						hit;
	int						side;
	int						wall_height;
	t_point					draw;
	int						color;
	int						tex_id;
	t_point					tex;
	double					wallhit;
}							t_ray;

typedef struct				s_floor
{
	t_matrix	floor;
	double		player_dist;
	double		dist;
	t_matrix	curr;
	t_point		ftext;
	double		w;
}							t_floor;

typedef struct				s_user
{
	SDL_Texture	*hood;
	SDL_Rect	texture;
}							t_ui;

typedef struct				s_sdl
{
	int				win_w;
	int				win_h;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*texture;
	SDL_Event		e;
	t_img			img;
	int				running;
}							t_sdl;

typedef struct				s_main
{
	t_sdl					sdl;
	t_map					map;
	t_player				player;
	t_frame					frame;
	t_keyboard				keys;
	Mix_Chunk				*sound;
	t_ui					inface;
	int						*texture[8];
	double					olddir;
	double					oldplane;
}							t_wolf;

void						error(char *str);
void						init_sdl(t_sdl *sdl, char *title);
t_img						create_image(size_t width, size_t height);
void						image_put(t_sdl *sdl);
void						clear_image(t_img *img);
void						pixel_put(t_img *img, int x, int y, int color);
void						parse_map(int fd, t_map *map);
void						read_dimension(int fd, t_map *map);
void						mallocd(t_map *map);
void						init_player(t_map *map, int height, int width);
void						parse_line(int *arr, char *line,
		t_map *map, int height);
void						init_text(t_wolf *w);
void						ray_cast(t_wolf *w);
int							set_color(unsigned int r,
		unsigned int g, unsigned int b);
void						sdl_hook(t_wolf *w);
void						time(t_frame *frame, t_wolf *w);
void						move(t_wolf *w);
void						cast_floor(t_ray *r, t_floor *f, t_wolf *w, int x);
void						calc(t_ray *r, t_floor *f);
void						setup_ray_dir(t_ray *r, t_wolf *w);
void						dda(t_ray *r, t_wolf *w);
void						draw_text(t_ray *r, t_wolf *w, int x);
void						walldist(t_ray *r, t_wolf *w);
void						wall_height(t_ray *r, t_wolf *w);
void						turning_right(t_wolf *w);
void						turning_left(t_wolf *w);
void						texture_free(t_wolf *w);
void						end(t_wolf *w);
void						mus(t_wolf *w);
#endif
