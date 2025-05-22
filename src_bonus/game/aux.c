/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 16:33:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"


/**
 * @brief Initializes the thread arguments for rendering.
 *
 * @param state The application state containing the game's data.
 * @return true if successful, false otherwise.
 */
static bool	init_thread_args(t_app_state *state)
{
	int i;
	int slice;
	
	state->args = ft_calloc(state->core_count, sizeof(t_args));
	if (!state->args)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	i = -1;
	slice = MAIN_WIDTH / state->core_count;
	while (++i< state->core_count)
	{
		state->args[i].st = state;
		state->args[i].start_col = i * slice;
		if (i == state->core_count - 1)
            state->args[i].end_col = MAIN_WIDTH;
        else
            state->args[i].end_col = state->args[i].start_col + slice;
	}
	return (true);
}

/**

 * @brief Initializes the mutex and condition variable for rendering synchronization.
 *
 * @param state The application state containing the game's data.
 * @return true if successful, false otherwise.
 */
static bool	init_render_sync(t_app_state *state)
{
	if (pthread_mutex_init(&state->render_mutex, NULL) != 0)
		return (ft_putstr_fd(ERR_MUTEX_INIT, 2), false);
	state->mutex_initialized = true;
	if (pthread_cond_init(&state->render_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&state->render_mutex);
		return (ft_putstr_fd(ERR_COND_INIT, 2), false);
	}
	state->cond_initialized = true;
	if (pthread_cond_init(&state->main_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&state->render_mutex);
		return (ft_putstr_fd(ERR_COND_INIT, 2), false);
	}
	state->main_initialized = true;
	state->render_ready = false;
	state->threads_done = 0;
	return (true);
}

/**
 * @brief Creates the rendering threads.
 *
 * @param state The application state containing the game's data.
 * @return true if successful, false otherwise.
 */
static bool	init_threads(t_app_state *state)
{
	int	i;

	state->threads = ft_calloc(state->core_count, sizeof(pthread_t));
	if (!state->threads)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	state->thread_can_render = ft_calloc(state->core_count, sizeof(bool));
	if (!state->thread_can_render)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	i = -1;
	while (++i < state->core_count)
	{
		state->args[i].index = i;
		if (pthread_create(&state->threads[i], NULL, raycast_routine,
				&state->args[i]) != 0)
		{
			ft_putstr_fd(ERR_THREAD_CREATE, 2);
			for (int j = 0; j < i; j++)
				pthread_cancel(state->threads[j]);
			free(state->threads);
			return (false);
		}
	}
	return (true);
}

/**
 * @brief Allocates memory for threads, arguments, and rendering buffers.
 *
 * @param state The application state containing the game's data.
 * @return true if successful, false otherwise.
 */
bool	init_threads_and_buffers(t_app_state *state)
{
	state->core_count = sysconf(_SC_NPROCESSORS_ONLN);
	if (state->core_count > MAX_THREADS)
		state->core_count = MAX_THREADS;
	if (state->core_count == 0)
		return (ft_putstr_fd(ERR_MLX_INIT, 2), false);
	if (!init_thread_args(state)
		|| !init_render_sync(state)
		|| !init_threads(state))
		return (false);
	if (!init_player_points(&state->player) || !init_fov_points(&state->player))
		return (false);
	prec_normal(state);
	if (!state->normal_x)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	return (true);
}

/**
 * @brief Initializes animation slots for each door found in the map.
 *
 * @param state The application state containing the map and anims array.
 * @param door_anim Pointer to the door animation info.
 */
void	init_door_anim_slots(t_app_state *state)
{
	int	anim_idx;
	int	y;
	int	x;

	anim_idx = 1;
	y = -1;
	while (++y < state->map->range.y)
	{
		x = -1;
		while (++x < state->map->range.x)
		{
			if (state->map->map[y][x] == 'D')
			{
				state->anims[anim_idx].anim_info = state->g.door_anim;
				state->anims[anim_idx].current_frame = 0;
				gettimeofday(&state->anims[anim_idx].frame_start, NULL);
				state->anims[anim_idx].is_started = false;
				state->anims[anim_idx].is_reversed = false;
				state->anims[anim_idx].map_point.x = x;
				state->anims[anim_idx].map_point.y = y;
				anim_idx++;
			}
		}
	}
}

/**
 * @brief Initializes animations for the face and doors.
 *
 * @param state The application state containing the game's data.
 */
bool	init_animations(t_app_state *state)
{
	state->anims = ft_calloc(state->map->door_count + 1, sizeof(t_anim_slot));
	if (!state->anims)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	state->anims[0].anim_info = state->g.face_anim;
	state->anims[0].current_frame = 0;
	gettimeofday(&state->anims[0].frame_start, NULL);
	state->anims[0].is_started = false;
	state->anims[0].is_reversed = false;
	state->anims[0].map_point.x = -1;
	state->anims[0].map_point.y = -1;
	init_door_anim_slots(state);
	return (true);
}