/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 14:39:41 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Calculates and displays the current frames per second (FPS) on 
 * the screen.
 * 
 * @param previous_sec The seconds part of the previous frame's timestamp.
 * @param previous_usec The microseconds part of the previous frame's 
 * timestamp.
 * @param st The application state containing the MiniLibX instance and 
 * window.
 */
static inline void	print_fps(time_t previous_sec, time_t previous_usec,
	t_app_state *st)
{
struct timeval	current;
int				frame_time;
int				fps;
char			*itoa;


gettimeofday(&current, NULL);
if (previous_sec != 0 || previous_usec != 0)
{
	frame_time = (current.tv_sec - previous_sec) * 1000000
		+ (current.tv_usec - previous_usec);
	if (frame_time > 0)
		fps = 1000000 / frame_time;
	else
		fps = 0;
}
else
{
	frame_time = 0;
	fps = 0;
}
itoa = ft_itoa(fps);
mlx_string_put(st->mlx, st->win, 10, 20, 0xFF0000, "FPS:");
mlx_string_put(st->mlx, st->win, 50, 20, 0xFF0000, itoa);
free(itoa);
}

static inline void	blit_face_frame(t_img *dst, t_img *src, int dst_x, int dst_y)
{
	int	color;
	int	x;
	int	y;

	y = -1;
	while (++y < src->height)
	{
		x = -1;
		while (++x < src->width)
		{
			color = *(unsigned int *)(src->data_addr + (y * src->size_line + x
						* (src->bpp / 8)));
			if (color == 0xFF00FF)
				continue ;
			draw_pixel(dst, dst_x + x, dst_y + y, color);
		}
	}
}

void	post_process(t_app_state *st, struct timeval *now)
{
	int frame;
	t_img *face_frame;

	frame = st->anims[0].current_frame;
	face_frame = &st->g.face_anim[frame].frame;
	if (st->g.face)
		blit_face_frame(&st->g.main_scene, face_frame, FACE_X, MAIN_HEIGHT
			- (FACE_Y + face_frame->height));
	if (st->g.fps)
		print_fps(now->tv_sec, now->tv_usec, st);
}