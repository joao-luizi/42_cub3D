/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:30:53 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 14:31:08 by tjorge-l         ###   ########.fr       */
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
	if (keycode == XK_plus || keycode == XK_KP_Add)
	{
		if (state->map->minimap_scale < 30)
			state->map->minimap_scale += 10;
	}
	if (keycode == XK_minus || keycode == XK_KP_Subtract)
	{
		if (state->map->minimap_scale > 10)
			state->map->minimap_scale -= 10;
	}
}

static void	handle_keypress_util(int keycode, t_app_state *state)
{
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
		if (anim && !anim->is_started)
			anim->is_start_requested = true;
	}
	handle_keypress_util(keycode, state);
	handle_player(keycode, state);
	handle_utils(keycode, state);
	return (0);
}
