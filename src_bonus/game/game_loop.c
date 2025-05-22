#include "../../inc_bonus/cub3d.h"

static inline bool	time_lapsed(struct timeval *frame_start,
		struct timeval *now)
{
	long	sec_diff;
	long	usec_diff;

	sec_diff = frame_start->tv_sec - now->tv_sec;
	usec_diff = frame_start->tv_usec - now->tv_usec;
	if (usec_diff < 0)
	{
		sec_diff -= 1;
		usec_diff += 1000000;
	}
	if (sec_diff < 0)
		return (true);
	if (sec_diff == 0 && usec_diff <= 0)
		return (true);
	return (false);
}

static inline void	update_face_anim(t_app_state *state)
{
	int				delay_seconds;
	struct timeval	*now;

	now = &state->previous_time;
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
		if (state->anims[0].frame_start.tv_usec >= (1000000
				- state->anims[0].anim_info->duration_ms * 1000))
		{
			state->anims[0].frame_start.tv_sec += 1;
			state->anims[0].frame_start.tv_usec -= 1000000;
		}
		state->anims[0].frame_start.tv_usec
			+= state->anims[0].anim_info->duration_ms * 1000;
		if (state->anims[0].current_frame == 0)
			state->anims[0].is_started = false;
	}
}
static inline void	update_anims(t_app_state *state)
{
	int				x;
	struct timeval	*now;

	now = &state->previous_time;
	x = 0;
	while (++x < state->map->door_count + 1)
	{
		if (state->anims[x].is_start_requested)
		{
			state->anims[x].is_reversed = false;
			state->anims[x].is_started = true;
			state->anims[x].is_start_requested = false;
			state->anims[x].frame_start.tv_sec = now->tv_sec;
			state->anims[x].frame_start.tv_usec = now->tv_usec;
		}
		else if (state->anims[x].is_started
			&& time_lapsed(&state->anims[x].frame_start, now))
		{
			if (state->anims[x].is_reversed)
				state->anims[x].current_frame = (state->anims[x].current_frame - 1);
			else
				state->anims[x].current_frame = (state->anims[x].current_frame + 1);
			if (state->anims[x].frame_start.tv_usec >= (1000000
					- state->anims[x].anim_info->duration_ms * 1000))
			{
				state->anims[x].frame_start.tv_sec += 1;
				state->anims[x].frame_start.tv_usec -= 1000000;
			}
			state->anims[x].frame_start.tv_usec
				+= state->anims[x].anim_info->duration_ms * 1000;
			if (state->anims[x].current_frame == 0 && state->anims[x].is_reversed)
			{
				state->anims[x].is_started = false;
				state->anims[x].is_reversed = false;	
				state->anims[x].frame_start.tv_usec = now->tv_usec;
				state->anims[x].frame_start.tv_sec = now->tv_sec;
			}
			if (state->anims[x].current_frame == 3 && !state->anims[x].is_reversed)
				state->anims[x].is_reversed = true;
		}
	}
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
	gettimeofday(&st->previous_time, NULL);
	update_face_anim(st);
	update_anims(st);
	update_player(st);
	render_main_scene(st);
	mlx_put_image_to_window(st->mlx, st->win, st->g.main_scene.img_ptr, 0, 0);

	return (0);
}