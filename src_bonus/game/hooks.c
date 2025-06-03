/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:55:59 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 18:36:53 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

int	mouse_move_handler(int x, int y, t_app_state *st)
{
	(void)y;
	if (x > MAIN_WIDTH - MAIN_WIDTH / 4)
	{
		st->player.turn_left_pressed = false;
		st->player.turn_right_pressed = true;
	}
	else if (x < MAIN_WIDTH / 4)
	{
		st->player.turn_left_pressed = true;
		st->player.turn_right_pressed = false;
	}
	else
	{
		st->player.turn_left_pressed = false;
		st->player.turn_right_pressed = false;
	}
	return (0);
}

/**
 * @brief Handles key release events and updates the player's state
 * accordingly.
 *
 * @param keycode The keycode of the released key.
 * @param state The application state containing the player's data.
 * @return Always returns 0.
 */
int	handle_keyrelease(int keycode, t_app_state *state)
{
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		state->player.shift_pressed = false;
	if (keycode == XK_Alt_L || keycode == XK_Alt_R)
		state->player.alt_pressed = false;
	if (keycode == XK_w)
		state->player.up_pressed = false;
	if (keycode == XK_s)
		state->player.down_pressed = false;
	if (keycode == XK_a)
		state->player.left_pressed = false;
	if (keycode == XK_d)
		state->player.right_pressed = false;
	if (keycode == XK_Left || keycode == XK_KP_Left)
		state->player.turn_left_pressed = false;
	if (keycode == XK_Right || keycode == XK_KP_Right)
		state->player.turn_right_pressed = false;
	return (0);
}

/**
 * @brief Handles the closing of the application, freeing resources and
 * exiting.
 *
 * @param state The application state containing the game's data.
 * @return Always returns 0.
 */
int	close_handler(t_app_state *state)
{
	pthread_mutex_lock(&state->render_mutex);
	state->exit_requested = true;
	pthread_cond_broadcast(&state->render_cond);
	pthread_mutex_unlock(&state->render_mutex);
	mlx_loop_end(state->mlx);
	free_state(state);
	exit(0);
	return (0);
}
