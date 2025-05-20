/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:55:59 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 16:54:34 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Handles player movement and direction based on key presses.
 *
 * @param keycode The keycode of the pressed key.
 * @param state The application state containing the player's data.
 */
static void	handle_player(int keycode, t_app_state *state)
{
	if (keycode == XK_w)
	{
		state->player.up_pressed = true;
		state->player.down_pressed = false;
	}
	else if (keycode == XK_s)
	{
		state->player.up_pressed = false;
		state->player.down_pressed = true;
	}
	else if (keycode == XK_a)
	{
		state->player.left_pressed = true;
		state->player.right_pressed = false;
	}
	else if (keycode == XK_d)
	{
		state->player.left_pressed = false;
		state->player.right_pressed = true;
	}
}

/**
 * @brief Handles utility actions such as toggling FPS display or
 * exiting the game.
 *
 * @param keycode The keycode of the pressed key.
 * @param state The application state containing the game's data.
 */
static void	handle_utils(int keycode, t_app_state *state)
{
	if (keycode == XK_F1 || keycode == F1_KEY)
		state->g.fps = !state->g.fps;
	if (keycode == XK_F2 || keycode == F2_KEY)
		state->g.face = !state->g.face;
	if (keycode == XK_F3 || keycode == F3_KEY)
		state->g.minimap = !state->g.minimap;
	if (keycode == XK_F4 || keycode == F4_KEY)
		state->g.fog = !state->g.fog;
	if (keycode == XK_Escape)
		close_handler(state);
}

/**
 * @brief Handles key press events and updates the player's state
 * accordingly.
 *
 * @param keycode The keycode of the pressed key.
 * @param state The application state containing the player's data.
 * @return Always returns 0.
 */
int	handle_keypress(int keycode, t_app_state *state)
{
	t_anim_slot	*anim;

	if (keycode == XK_space || keycode == SPACE)
	{
		anim = find_door_anim(state, state->player.position.x
				+ state->player.direction.x, state->player.position.y
				+ state->player.direction.y);
		if (anim && !anim->is_reversed)
		{
			anim->is_reversed = false;
			anim->is_started = true;
		}
	}
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		state->player.shift_pressed = true;
	if (keycode == XK_Alt_L || keycode == XK_Alt_R)
		state->player.alt_pressed = true;
	if (keycode == XK_Left || keycode == XK_KP_Left)
	{
		state->player.turn_left_pressed = true;
		state->player.turn_right_pressed = false;
	}
	else if (keycode == XK_Right || keycode == XK_KP_Right)
	{
		state->player.turn_left_pressed = false;
		state->player.turn_right_pressed = true;
	}
	handle_player(keycode, state);
	handle_utils(keycode, state);
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
int close_handler(t_app_state *state)
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
