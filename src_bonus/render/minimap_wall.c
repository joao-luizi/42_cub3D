/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:15:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 11:25:06 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

bool	is_local_wall(t_app_state *st, int x, int y)
{
	int		map_x;
	int		map_y;
	double	angle;

	angle = atan2(st->player.direction.y, st->player.direction.x) + M_PI_2;
	map_x = (int)(st->player.position.x + (cos(angle) * ((x - MINIMAP_WIDTH / 2)
					/ (double)st->map->minimap_scale) - sin(angle) * ((y
						- MINIMAP_HEIGHT / 2)
					/ (double)st->map->minimap_scale)));
	map_y = (int)(st->player.position.y + (sin(angle) * ((x - MINIMAP_WIDTH / 2)
					/ (double)st->map->minimap_scale) + cos(angle) * ((y
						- MINIMAP_HEIGHT / 2)
					/ (double)st->map->minimap_scale)));
	if (map_x < 0 || map_x >= st->map->range.x || map_y < 0
		|| map_y >= st->map->range.y)
		return (false);
	return (st->map->map[map_y][map_x] == '1');
}

static int	calc_map_x(t_app_state *st, double angle, int x, int y)
{
	return ((int)(st->player.position.x + (cos(angle) * ((x - MINIMAP_WIDTH / 2)
				/ (double)st->map->minimap_scale) - sin(angle) * ((y
					- MINIMAP_HEIGHT / 2)
				/ (double)st->map->minimap_scale))));
}

static int	calc_map_y(t_app_state *st, double angle, int x, int y)
{
	return ((int)(st->player.position.y + (sin(angle) * ((x - MINIMAP_WIDTH / 2)
				/ (double)st->map->minimap_scale) + cos(angle) * ((y
					- MINIMAP_HEIGHT / 2)
				/ (double)st->map->minimap_scale))));
}

int	get_local_wall_color(t_app_state *st, int x, int y)
{
	int			map_x;
	int			map_y;
	double		angle;
	t_anim_slot	*door_anim;

	angle = atan2(st->player.direction.y, st->player.direction.x) + M_PI_2;
	map_x = calc_map_x(st, angle, x, y);
	map_y = calc_map_y(st, angle, x, y);
	if (map_x < 0 || map_x >= st->map->range.x || map_y < 0
		|| map_y >= st->map->range.y)
		return (0xFF00FF);
	if (st->map->map[map_y][map_x] == '1')
		return (0xFFFFFF);
	if (st->map->map[map_y][map_x] == 'D')
	{
		door_anim = find_door_anim(st, map_x, map_y);
		if (door_anim && door_anim->current_frame == 0)
			return (0x00FF00);
	}
	return (0x808080);
}
