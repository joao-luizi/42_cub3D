/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:17:39 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 11:18:17 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static inline int	blend_color(int color1, int color2, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = ((color1 >> 16) & 0xFF) * (1 - ratio) + ((color2 >> 16) & 0xFF) * ratio;
	g = ((color1 >> 8) & 0xFF) * (1 - ratio) + ((color2 >> 8) & 0xFF) * ratio;
	b = (color1 & 0xFF) * (1 - ratio) + (color2 & 0xFF) * ratio;
	return ((r << 16) | (g << 8) | b);
}

int	get_local_color(int x)
{
	double	blend_ratio;
	int		color;

	if (x > FOV_D / 4)
	{
		blend_ratio = (double)(x - FOV_D / 4) / (FOV_D - FOV_D / 4);
		color = blend_color(0x45D4FF, 0x808080, blend_ratio);
	}
	else
		color = 0x45D4FF;
	return (color);
}

int	get_color(t_app_state *st, int x, int y)
{
	if (is_player(st, x, y))
		return (0xFF0000);
	else
		return (get_local_wall_color(st, x, y));
}
