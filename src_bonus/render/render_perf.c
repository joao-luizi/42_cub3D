/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_perf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 13:05:20 by joaomigu         ###   ########.fr       */
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
void	prec_normal_x(double **normal_x, int width)
{
	int	x;

	*normal_x = ft_calloc(width, sizeof(double));
	if (!(*normal_x))
	{
		ft_putstr_fd(ERR_ALLOC_FAIL, 2);
		exit(EXIT_FAILURE);
	}
	x = -1;
	while (++x < width)
		(*normal_x)[x] = 2 * x / (double)width - 1;
}
