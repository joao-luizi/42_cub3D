#include "../../inc_bonus/cub3d.h"

void	blit_face_frame(t_img *dst, t_img *src, int dst_x, int dst_y)
{
	int	color;
	int x;
	int y;

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

static inline bool time_lapsed(struct timeval *frame_start, struct timeval *now)
{
    long sec_diff = frame_start->tv_sec - now->tv_sec;
    long usec_diff = frame_start->tv_usec - now->tv_usec;

    if (usec_diff < 0)
    {
        sec_diff -= 1;
        usec_diff += 1000000;
    }
    if (sec_diff < 0)
        return true;
    if (sec_diff == 0 && usec_diff <= 0)
        return true;
    return false;
}

static inline void update_face_anim(t_app_state *state, struct timeval *now)
{
	int		delay_seconds;

	if (!state->anims[0].is_started)
	{
		state->anims[0].current_frame = 0;
		state->anims[0].is_started = true;
		delay_seconds = 10 + rand() % 6;
		state->anims[0].frame_start.tv_sec = now->tv_sec + delay_seconds;
		state->anims[0].frame_start.tv_usec = now->tv_usec;
	}
    if (time_lapsed(&state->anims[0].frame_start, now))
    {
        state->anims[0].current_frame = (state->anims[0].current_frame + 1) % 4;
		if (state->anims[0].frame_start.tv_usec >= (1000000 - state->anims[0].anim_info->duration_ms * 1000))
		{
			state->anims[0].frame_start.tv_sec += 1;
			state->anims[0].frame_start.tv_usec -= 1000000;
		}
		state->anims[0].frame_start.tv_usec += state->anims[0].anim_info->duration_ms * 1000; 
		if (state->anims[0].current_frame == 0)
			state->anims[0].is_started = false;    
    }

}
static inline void	update_anims(t_app_state *state, struct timeval *now)
{
	int		x;
	
	x = -1;
	while (++x < state->map->door_count + 1)
	{
		if (state->anims[x].is_started)
		{
			if (time_lapsed(&state->anims[0].frame_start, now))
			{
				if (state->anims[x].is_reversed)
				{
					if (state->anims[x].current_frame > 0)
						state->anims[x].current_frame--;
					else
					{
						state->anims[x].is_reversed = false;
						state->anims[x].is_started = false;;
					}
				}
				else
				{
					state->anims[x].current_frame++;
					if (state->anims[x].current_frame > 2)
						state->anims[x].is_reversed = true;
				}
				gettimeofday(&state->anims[x].frame_start, NULL);
				state->anims[x].frame_start.tv_sec += state->anims[x].anim_info->duration_ms / 1000;
			}
		}
	}
}

static inline void post_process(t_app_state *st, struct timeval	*now)
{
	int frame;
	t_img *face_frame;

	frame = st->anims[0].current_frame;
	face_frame = &st->g.face_anim[frame].frame;
	if (st->g.face)
		blit_face_frame(&st->g.main_scene, face_frame, FACE_X, MAIN_HEIGHT - (FACE_Y + face_frame->height));
	if (st->g.fps)
		print_fps(now->tv_sec, now->tv_usec, st);
}
/**
 * @brief The main game loop that updates the player, renders the scene,
 * and displays FPS.
 *
 * @param st The application state containing the game's data.
 * @return Always returns 0.
 */
int	game_loop(t_app_state *st)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	
	//evaluate graphic quality, if lacking include
	//mlx_clear_window(st->mlx, st->win);

	update_face_anim(st, &now);
	update_anims(st, &now);
	update_player(st);
	render_main_scene(st);


	post_process(st, &now);
	mlx_put_image_to_window(st->mlx, st->win, st->g.main_scene.img_ptr, 0, 0);
	
	return (0);
}