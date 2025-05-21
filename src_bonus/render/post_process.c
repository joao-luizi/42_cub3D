/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/21 12:36:16 by joaomigu         ###   ########.fr       */
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
void	print_fps(t_app_state *st)
{
	struct timeval	current;
	int				frame_time;
	int				fps;
	char			*itoa;

	gettimeofday(&current, NULL);
	if (st->previous_time.tv_sec != 0 || st->previous_time.tv_usec != 0)
	{
		frame_time = (current.tv_sec - st->previous_time.tv_sec) * 1000000
			+ (current.tv_usec - st->previous_time.tv_usec);
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
	lib_x_write_string("FPS", 10, 20, &st->g.main_scene);
	lib_x_write_string(itoa, 80, 20, &st->g.main_scene);
	free(itoa);
	itoa = ft_itoa(st->core_count);
	lib_x_write_string("CORES", 10, 50, &st->g.main_scene);
	lib_x_write_string(itoa, 80, 50, &st->g.main_scene);
	free(itoa);
}

static inline void	blit_face_frame(t_img *dst, t_img *src, int dst_x,
		int dst_y)
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

void	post_process(t_app_state *st)
{
	int frame;
	t_img *face_frame;

	frame = st->anims[0].current_frame;
	face_frame = &st->g.face_anim[frame].frame;
	if (st->g.face)
		blit_face_frame(&st->g.main_scene, face_frame, FACE_X, MAIN_HEIGHT
			- (FACE_Y + face_frame->height));
	if (st->g.fps)
		print_fps(st);
}