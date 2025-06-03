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
