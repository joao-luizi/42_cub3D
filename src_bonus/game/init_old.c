/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/17 17:19:25 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void	blit_face_frame(t_img *dst, t_img *src, int dst_x, int dst_y)
{
    int	x, y;
    int	color;

    for (y = 0; y < src->height; ++y)
    {
        for (x = 0; x < src->width; ++x)
        {
            color = *(unsigned int *)(src->data_addr + (y * src->size_line + x * (src->bpp / 8)));
            if (color == 0xFF00FF) 
                continue;
            draw_pixel(dst, dst_x + x, dst_y + y, color);
        }
    }
}

static inline long	timeval_diff_ms(struct timeval *a, struct timeval *b)
{
	// Returns the difference in milliseconds between a and b (a - b)
	return ((a->tv_sec - b->tv_sec) * 1000L + (a->tv_usec - b->tv_usec)
		/ 1000L);
}

static inline void	update_anims(t_app_state *state, struct timeval *now)
{
	int		x;
	int		delay_ms;
	long	elapsed;
	int		duration;

	x = -1;
	while (++x < state->map->door_count + 1)
	{
		if (x == 0 && !state->anims[x].is_started)
		{
			delay_ms = 1000 + rand() % 2000;
			state->anims[x].frame_start.tv_sec = now->tv_sec + delay_ms / 1000;
			state->anims[x].frame_start.tv_usec = now->tv_usec + (delay_ms
					% 1000) * 1000;
			if (state->anims[x].frame_start.tv_usec >= 1000000)
			{
				state->anims[x].frame_start.tv_sec += 1;
				state->anims[x].frame_start.tv_usec -= 1000000;
			}
			state->anims[x].current_frame = 0;
			state->anims[0].is_started = true;
		}
		if (state->anims[x].is_started)
		{
			elapsed = timeval_diff_ms(now, &state->anims[x].frame_start);
			duration = state->anims[x].anim_info->duration_ms;
			if (elapsed >= duration)
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
				state->anims[x].frame_start.tv_sec += duration / 1000;
				state->anims[x].frame_start.tv_usec += (duration % 1000) * 1000;
				if (state->anims[x].frame_start.tv_usec >= 1000000)
				{
					state->anims[x].frame_start.tv_sec += 1;
					state->anims[x].frame_start.tv_usec -= 1000000;
				}
			}
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
static inline int	game_loop(t_app_state *st)
{
	struct timeval	va;

	gettimeofday(&va, NULL);
	mlx_clear_window(st->mlx, st->win);
	update_anims(st, &va);
	update_player(st);
	render_main_scene(st);
	int frame = st->anims[0].current_frame;
	t_img *face_frame = &st->g.face_anim[frame].frame;
	blit_face_frame(&st->g.main_scene, face_frame, FACE_X, MAIN_HEIGHT - (FACE_Y + face_frame->height));
	mlx_put_image_to_window(st->mlx, st->win, st->g.main_scene.img_ptr, 0, 0);
	if (st->g.fps)
		print_fps(va.tv_sec, va.tv_usec, st);
	return (0);
}

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
static bool init_window_and_image(t_app_state *state)
{
    state->win = mlx_new_window(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    if (!state->win)
        return (ft_putstr_fd(ERR_WIN_INIT, 2), false);
    if (!init_mlx_image(&state->g.main_scene, state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT))
        return (ft_putstr_fd(ERR_IMG_INIT, 2), false);
    return true;
}

/**
 * @brief Allocates memory for threads, arguments, and rendering buffers.
 *
 * @param state The application state containing the game's data.
 * @return true if successful, false otherwise.
 */
static bool init_threads_and_buffers(t_app_state *state)
{
    state->core_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (state->core_count > MAX_THREADS)
        state->core_count = MAX_THREADS;
    if (state->core_count == 0)
        return (ft_putstr_fd(ERR_MLX_INIT, 2), false);
    state->args = ft_calloc(state->core_count, sizeof(t_args));
    if (!state->args)
        return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
    state->threads = ft_calloc(state->core_count, sizeof(pthread_t));
    if (!state->threads)
        return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
    state->column_buffer = ft_calloc(MAIN_HEIGHT, sizeof(int));
    state->door_buffer = ft_calloc(MAIN_HEIGHT, sizeof(int));
    if (!state->column_buffer || !state->door_buffer)
        return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
    prec_normal_x(&state->normal_x, MAIN_WIDTH);
    if (!state->normal_x)
        return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
    return true;
}

/**
 * @brief Initializes animations for the face and doors.
 *
 * @param state The application state containing the game's data.
 */
static void init_animations(t_app_state *state)
{
    state->anims = ft_calloc(state->map->door_count + 1, sizeof(t_anim_slot));
    if (!state->anims)
        return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), (void)0);
    state->anims[0].anim_info = state->g.face_anim;
    state->anims[0].current_frame = 0;
    gettimeofday(&state->anims[0].frame_start, NULL);
    state->anims[0].is_started = false;
    state->anims[0].is_reversed = false;
    state->anims[0].map_point.x = -1;
    state->anims[0].map_point.y = -1;
    init_door_anim_slots(state);
}

/**
 * @brief Sets up event hooks for the game loop and input handling.
 *
 * @param state The application state containing the game's data.
 */
static void init_hooks(t_app_state *state)
{
    mlx_hook(state->win, KeyPress, KeyPressMask, handle_keypress, state);
    mlx_hook(state->win, KeyRelease, KeyReleaseMask, handle_keyrelease, state);
    mlx_hook(state->win, DestroyNotify, StructureNotifyMask, close_handler, state);
    mlx_loop_hook(state->mlx, game_loop, state);
}

/**
 * @brief Initializes the game by setting up the window, threads, buffers,
 * animations, and event hooks.
 *
 * @param state The application state containing the game's data.
 */
void init_game(t_app_state *state)
{
    if (!init_window_and_image(state))
        return;
    if (!init_threads_and_buffers(state))
        return;
    init_animations(state);
    init_hooks(state);
    mlx_loop(state->mlx);
}

/**
 * @brief Initializes the game window and sets up hooks for events and
 * the game loop.
 *
 * @param state The application state containing the game's data.
 */
void	init_window(t_app_state *state)
{
	state->win = mlx_new_window(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (!state->win)
		return (ft_putstr_fd(ERR_WIN_INIT, 2), (void)0);
	if (!init_mlx_image(&state->g.main_scene, state->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT))
		return (ft_putstr_fd(ERR_IMG_INIT, 2), (void)0);
	state->core_count = sysconf(_SC_NPROCESSORS_ONLN);
	if (state->core_count > MAX_THREADS)
		state->core_count = MAX_THREADS;
	if (state->core_count == 0)
		return (ft_putstr_fd(ERR_MLX_INIT, 2), (void)0);
	state->args = ft_calloc(state->core_count, sizeof(t_args));
	if (!state->args)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), (void)0);
	state->threads = ft_calloc(state->core_count, sizeof(pthread_t));
	if (!state->threads)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), (void)0);
	prec_normal_x(&state->normal_x, MAIN_WIDTH);
	state->column_buffer = ft_calloc(MAIN_HEIGHT, sizeof(int));
	state->door_buffer = ft_calloc(MAIN_HEIGHT, sizeof(int));
	state->anims = ft_calloc(state->map->door_count + 1, (sizeof(t_anim_slot)));
	if (!state->normal_x || !state->column_buffer || !state->anims || !state->door_buffer)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), (void)0);
	state->anims[0].anim_info = state->g.face_anim;
	state->anims[0].current_frame = 0;
	gettimeofday(&state->anims[0].frame_start, NULL);
	state->anims[0].is_started = false;
	state->anims[0].is_reversed = false;
	state->anims[0].map_point.x = -1;
	state->anims[0].map_point.y = -1;
	init_door_anim_slots(state);
	mlx_hook(state->win, KeyPress, KeyPressMask, handle_keypress, state);
	mlx_hook(state->win, KeyRelease, KeyReleaseMask, handle_keyrelease, state);
	mlx_hook(state->win, DestroyNotify, StructureNotifyMask, close_handler,
		state);
	mlx_loop_hook(state->mlx, game_loop, state);
	mlx_loop(state->mlx);
}
