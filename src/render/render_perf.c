/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_perf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/13 15:47:37 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void prec_normal_x(double **normal_x, int width)
{
    int x;

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

