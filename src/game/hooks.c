/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:55:59 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 17:56:20 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

static void	handle_utils(int keycode, t_app_state *state)
{
	if (keycode == XK_F1 || keycode == F1_KEY)
		state->g.fps = !state->g.fps;
	if (keycode == XK_Escape)
	{
		mlx_loop_end(state->mlx);
		free_state(state);
		exit(0);
	}
}

int	handle_keypress(int keycode, t_app_state *state)
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
	handle_player(keycode, state);
	handle_utils(keycode, state);
	return (0);
}

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

int	close_handler(t_app_state *state)
{
	mlx_loop_end(state->mlx);
	free_state(state);
	exit(0);
	return (0);
}
