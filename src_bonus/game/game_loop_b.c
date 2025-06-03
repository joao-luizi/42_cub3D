/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:02:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 15:03:12 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

bool	time_lapsed(struct timeval *frame_start,
		struct timeval *now)
{
	long	sec_diff;
	long	usec_diff;

	sec_diff = frame_start->tv_sec - now->tv_sec;
	usec_diff = frame_start->tv_usec - now->tv_usec;
	if (usec_diff < 0)
	{
		sec_diff -= 1;
		usec_diff += 1000000;
	}
	if (sec_diff < 0)
		return (true);
	if (sec_diff == 0 && usec_diff <= 0)
		return (true);
	return (false);
}
