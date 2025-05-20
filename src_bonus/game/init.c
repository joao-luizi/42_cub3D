/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 15:28:46 by joaomigu         ###   ########.fr       */
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
	if (!init_mlx_image(&state->g.buffer, state->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT))
		return (ft_putstr_fd(ERR_IMG_INIT, 2), false);
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
