/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 13:05:27 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Calculates and displays the current frames per second (FPS) on 
 * the screen.
 * 
 * @param previous_sec The seconds part of the previous frame's timestamp.
 * @param previous_usec The microseconds part of the previous frame's 
 * timestamp.
 * @param st The application state containing the MiniLibX instance and 
 * window.
 */
void	print_fps(time_t previous_sec, time_t previous_usec,
		t_app_state *st)
{
	struct timeval	current;
	int				frame_time;
	int				fps;
	char			*itoa;

	gettimeofday(&current, NULL);
	if (previous_sec != 0 || previous_usec != 0)
	{
		frame_time = (current.tv_sec - previous_sec) * 1000000
			+ (current.tv_usec - previous_usec);
		if (frame_time > 0)
			fps = 1000000 / frame_time;
		else
			fps = 0;
	}
	else
	{
		frame_time = 0;
		fps = 0;
	}
	itoa = ft_itoa(fps);
	mlx_string_put(st->mlx, st->win, 10, 20, 0xFF0000, "FPS:");
	mlx_string_put(st->mlx, st->win, 50, 20, 0xFF0000, itoa);
	free(itoa);
}
