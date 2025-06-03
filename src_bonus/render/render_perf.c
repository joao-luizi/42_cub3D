/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_perf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/24 14:24:25 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Precomputes normalized x-coordinates for a given screen width.
 * 
 * This function allocates and fills an array with normalized x-coordinates
 * ranging from -1 to 1, which can be used for raycasting or other rendering
 * calculations.
 * 
 * @param normal_x Pointer to the array of normalized x-coordinates to 
 * allocate and fill.
 * @param width The width of the screen or rendering surface.
 */
void	prec_normal(t_app_state *st)
{
	int	x;
	int	idy;

	st->normal_x = ft_calloc(MAIN_WIDTH, sizeof(double));
	st->normal_y = ft_calloc(MAIN_HEIGHT / 2, sizeof(double));
	if (!st->normal_x || !st->normal_y)
	{
		ft_putstr_fd(ERR_ALLOC_FAIL, 2);
		exit(EXIT_FAILURE);
	}
	x = -1;
	while (++x < MAIN_WIDTH)
		st->normal_x[x] = 2 * x / (double)MAIN_WIDTH - 1;
	x = MAIN_HEIGHT / 2 - 1;
	idy = 0;
	while (x >= 0)
	{
		st->normal_y[idy] = (0.5 * MAIN_HEIGHT) / (MAIN_HEIGHT / 2 - x);
		x--;
		idy++;
	}
}
