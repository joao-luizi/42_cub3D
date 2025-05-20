/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:12:32 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 18:40:19 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Rotates the player by a given rotation speed.
 *
 * @param state The application state containing the player's data.
 * @param rotation_speed The speed and direction of the rotation.
 */
static inline void	rotate_player(t_app_state *state, t_vector rotation_speed)
{
	double	old_d_x;
	double	old_plane_x;

	old_d_x = state->player.direction.x;
	state->player.direction.x = state->player.direction.x * rotation_speed.x
		- state->player.direction.y * rotation_speed.y;
	state->player.direction.y = old_d_x * rotation_speed.y
		+ state->player.direction.y * rotation_speed.x;
	old_plane_x = state->player.plane.x;
	state->player.plane.x = state->player.plane.x * rotation_speed.x
		- state->player.plane.y * rotation_speed.y;
	state->player.plane.y = old_plane_x * rotation_speed.y
		+ state->player.plane.y * rotation_speed.x;
}

/**
 * @brief Moves the player by a given velocity vector, checking for 
 * collisions.
 *
 * @param v_x The velocity in the x-direction.
 * @param v_y The velocity in the y-direction.
 * @param state The application state containing the player's data.
 */
static inline void	move_player(double v_x, double v_y, t_app_state *state)
{
	double	new_x;
	double	new_y;
	double	buffer_x;
	double	buffer_y;

	if (v_x > 0)
		buffer_x = 0.5;
	else
		buffer_x = 0.5;
	if (v_y > 0)
		buffer_y = 0.5;
	else
		buffer_y = 0.5;
	new_x = state->player.position.x + v_x;
	new_y = state->player.position.y + v_y;
	if (!is_wall(new_x + buffer_x, state->player.position.y, state))	// Need to understand this check better.
		state->player.position.x = new_x;
	if (!is_wall(state->player.position.x, new_y + buffer_y, state))
		state->player.position.y = new_y;
}

/**
 * @brief Calculates the vertical movement of the player based on input.
 *
 * @param state The application state containing the player's data.
 * @param v_x Pointer to the x-component of the velocity vector.
 * @param v_y Pointer to the y-component of the velocity vector.
 * @param move_speed The speed of the player's movement.
 */
static inline void	vertical_move(t_app_state *state, double *v_x, double *v_y,
		double move_speed)
{
	if (state->player.up_pressed)
	{
		*v_x += state->player.direction.x * move_speed;
		*v_y += state->player.direction.y * move_speed;
	}
	if (state->player.down_pressed)
	{
		*v_x += -state->player.direction.x * move_speed;
		*v_y += -state->player.direction.y * move_speed;
	}
}

/**
 * @brief Calculates the horizontal movement of the player based on input.
 *
 * @param state The application state containing the player's data.
 * @param v_x Pointer to the x-component of the velocity vector.
 * @param v_y Pointer to the y-component of the velocity vector.
 * @param move_speed The speed of the player's movement.
 */
static inline void	horizontal_move(t_app_state *state, double *v_x,
		double *v_y, double move_speed)
{
	if (state->player.left_pressed)
	{
		*v_x += state->player.direction.y * move_speed;
		*v_y += -state->player.direction.x * move_speed;
	}
	else if (state->player.right_pressed)
	{
		*v_x += -state->player.direction.y * move_speed;
		*v_y += state->player.direction.x * move_speed;
	}
	if (state->player.turn_left_pressed)
		rotate_player(state, state->player.rotation_factor_neg);
	if (state->player.turn_right_pressed)
		rotate_player(state, state->player.rotation_factor_pos);
}

/**
 * @brief Updates the player's position and orientation based on input.
 *
 * @param state The application state containing the player's data.
 */
void	update_player(t_app_state *state)
{
	double	v_x;
	double	v_y;
	double	move_speed;

	move_speed = state->player.speed.linear;
	if (state->player.shift_pressed)
		move_speed *= 1.5;
	v_x = 0;
	v_y = 0;
	vertical_move(state, &v_x, &v_y, move_speed);
	horizontal_move(state, &v_x, &v_y, move_speed);
	if (v_x || v_y)
		move_player(v_x, v_y, state);
}
