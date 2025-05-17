/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/17 18:49:28 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"


/**
 * @brief Initializes a MiniLibX image with the specified dimensions.
 *
 * @param img The image structure to initialize.
 * @param mlx The MiniLibX instance.
 * @param width The width of the image.
 * @param height The height of the image.
 * @return true if the image was successfully initialized, false otherwise.
 */
static bool	init_mlx_image(t_img *img, void *mlx, int width, int height)
{
	img->img_ptr = mlx_new_image(mlx, width, height);
	if (!img->img_ptr)
		return (ft_putstr_fd(ERR_IMG_INIT, 2), false);
	img->height = height;
	img->width = width;
	img->half_height = height / 2;
	img->half_width = width / 2;
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->data_addr)
		return (ft_putstr_fd(ERR_IMG_DA, 2), false);
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
 * @brief Initializes the MiniLibX window and main scene image.
 *
 * @param state The application state containing the game's data.
 * @return true if successful, false otherwise.
 */
static bool	init_window_and_image(t_app_state *state)
{
	state->win = mlx_new_window(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (!state->win)
		return (ft_putstr_fd(ERR_WIN_INIT, 2), false);
	if (!init_mlx_image(&state->g.main_scene, state->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT))
		return (ft_putstr_fd(ERR_IMG_INIT, 2), false);
	return (true);
}

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
            state->args[i].end_col = (i + 1) * slice;
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
	if (pthread_cond_init(&state->render_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&state->render_mutex);
		return (ft_putstr_fd(ERR_COND_INIT, 2), false);
	}
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
	i = -1;
	while (++i < state->core_count)
	{
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
static bool	init_threads_and_buffers(t_app_state *state)
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
	prec_normal_x(&state->normal_x, MAIN_WIDTH);
	if (!state->normal_x)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	return (true);
}

/**
 * @brief Initializes animations for the face and doors.
 *
 * @param state The application state containing the game's data.
 */
static bool	init_animations(t_app_state *state)
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

/**
 * @brief Sets up event hooks for the game loop and input handling.
 *
 * @param state The application state containing the game's data.
 */
static void	init_hooks(t_app_state *state)
{
	mlx_hook(state->win, KeyPress, KeyPressMask, handle_keypress, state);
	mlx_hook(state->win, KeyRelease, KeyReleaseMask, handle_keyrelease, state);
	mlx_hook(state->win, DestroyNotify, StructureNotifyMask, close_handler,
		state);
	mlx_loop_hook(state->mlx, game_loop, state);
}

/**
 * @brief Initializes the game by setting up the window, threads, buffers,
 * animations, and event hooks.
 *
 * @param state The application state containing the game's data.
 */
void	init_game(t_app_state *state)
{
	if (!init_window_and_image(state)
		|| !init_threads_and_buffers(state)
		|| !init_animations(state))
		return ;
	init_hooks(state);
	mlx_loop(state->mlx);
}
