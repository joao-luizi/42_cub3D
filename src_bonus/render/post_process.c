/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 16:58:05 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static void	print_fps_util(t_app_state *st, int fps)
{
	char	*itoa;

	itoa = ft_itoa(fps);
	if (!itoa)
		return ;
	lib_x_write_string("FPS", FPS_X + 10, FPS_Y + 20, &st->g.main_scene);
	lib_x_write_string(itoa, FPS_X + 80, FPS_Y + 20, &st->g.main_scene);
	free(itoa);
	itoa = ft_itoa(st->core_count);
	if (!itoa)
		return ;
	lib_x_write_string("CORES", FPS_X + 10, FPS_Y, &st->g.main_scene);
	lib_x_write_string(itoa, FPS_X + 80, FPS_Y, &st->g.main_scene);
	free(itoa);
}

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
	print_fps_util(st, fps);
}

static inline void	blit_face_frame(t_img *dst, t_img *src,
									t_point p, t_args *args)
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
			if (x + p.x < args->start_col
				|| x + p.x >= args->end_col)
				continue ;
			color = *(unsigned int *)(src->data_addr + (y * src->size_line + x
						* (src->bpp / 8)));
			if (color == 0xFF00FF)
				continue ;
			draw_pixel(dst, p.x + x, p.y + y, color);
		}
	}
}

static bool	belongs_in_slice(t_args *args, int x)
{
	return (x >= args->start_col && x < args->end_col);
}

void	post_process(t_app_state *st, t_args *args)
{
	int		frame;
	t_img	*face_frame;

	frame = st->anims[0].current_frame;
	face_frame = &st->g.face_anim[frame].frame;
	if (st->g.face && (belongs_in_slice(args, FACE_X)
			|| belongs_in_slice(args, FACE_X + face_frame->width)))
		blit_face_frame(&st->g.main_scene,
			face_frame, (t_point){FACE_X, MAIN_HEIGHT
			- (FACE_Y + face_frame->height)}, args);
	if (st->g.fps && (belongs_in_slice(args, FPS_X)
			|| belongs_in_slice(args, FPS_X + face_frame->width)))
		print_fps(st);
	if (st->g.minimap && (belongs_in_slice(args, MINIMAP_X)
			|| belongs_in_slice(args, MINIMAP_X + MINIMAP_WIDTH)))
		render_minimap(st, args);
}
