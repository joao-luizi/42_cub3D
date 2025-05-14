/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:12:32 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 17:56:12 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static inline void	rotate_player(t_app_state *state, double rotation_speed)
{
	double	old_d_x;
	double	old_plane_x;

	old_d_x = state->player.direction.x;
	state->player.direction.x = state->player.direction.x * cos(rotation_speed)
		- state->player.direction.y * sin(rotation_speed);
	state->player.direction.y = old_d_x * sin(rotation_speed)
		+ state->player.direction.y * cos(rotation_speed);
	old_plane_x = state->player.plane.x;
	state->player.plane.x = state->player.plane.x * cos(rotation_speed)
		- state->player.plane.y * sin(rotation_speed);
	state->player.plane.y = old_plane_x * sin(rotation_speed)
		+ state->player.plane.y * cos(rotation_speed);
}

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
	if (!is_wall(new_x + buffer_x, state->player.position.y, state))
		state->player.position.x = new_x;
	if (!is_wall(state->player.position.x, new_y + buffer_y, state))
		state->player.position.y = new_y;
}

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
		rotate_player(state, -state->player.speed.angular);
	if (state->player.turn_right_pressed)
		rotate_player(state, state->player.speed.angular);
}

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
