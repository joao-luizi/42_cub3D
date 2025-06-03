/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:57:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 11:11:51 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

bool	is_player(t_app_state *st, int x, int y)
{
	int	scale_index;

	if (st->map->minimap_scale == 10)
		scale_index = 0;
	else if (st->map->minimap_scale == 20)
		scale_index = 1;
	else
		scale_index = 2;
	return (st->player.triangle_points[scale_index][y][x]);
}

static void	render_fov_util(t_app_state *st, t_args *args, int y)
{
	int	x;
	int	color;

	x = -1;
	while (++x < FOV_D)
	{
		if (x >= args->start_col && x <= args->end_col)
		{
			color = get_local_wall_color(st, st->player.fov_points[y][x].x,
					st->player.fov_points[y][x].y);
			if (color != 0x808080)
				break ;
			if (!is_player(st, st->player.fov_points[y][x].x,
				st->player.fov_points[y][x].y))
			{
				color = get_local_color(x);
				draw_pixel(&st->g.main_scene, st->player.fov_points[y][x].x,
					st->player.fov_points[y][x].y, color);
			}
		}
	}
}

// if (color != 0x808080)
// 	break ;
// // if (is_local_wall(st, st->player.fov_points[y][x].x,
// //		st->player.fov_points[y][x].y))
// //		break ;

static inline void	render_fov(t_app_state *st, t_args *args)
{
	int	y;

	y = -1;
	while (++y < FOV * 2)
	{
		render_fov_util(st, args, y);
	}
}

void	render_minimap(t_app_state *st, t_args *args)
{
	int	y;
	int	x;
	int	color;

	if (!st->g.minimap)
		return ;
	if (MINIMAP_X + MINIMAP_WIDTH < args->start_col
		|| MINIMAP_X > args->end_col)
		return ;
	y = -1;
	while (++y < MINIMAP_HEIGHT)
	{
		x = -1;
		while (++x < MINIMAP_WIDTH)
		{
			if (x >= args->start_col && x < args->end_col)
			{
				color = get_color(st, x, y);
				if (color != 0xFF00FF)
					draw_pixel(&st->g.main_scene, x, y, get_color(st, x, y));
			}
		}
	}
	render_fov(st, args);
}
