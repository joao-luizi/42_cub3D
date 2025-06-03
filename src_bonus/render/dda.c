/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:27:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 13:28:20 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static void	get_obs_info_util(t_app_state *st, t_obstacle *obs)
{
	if (st->g.fog == true)
	{
		if (obs->dist >= MAX_DISTANCE)
			obs->blending_factor = 1.0f;
		else
			obs->blending_factor = obs->dist / MAX_DISTANCE;
	}
	else
		obs->blending_factor = 0.0f;
}

static inline void	get_obs_info(t_app_state *st,
						t_ray_info *r_info, int side, bool is_wall)
{
	t_obstacle	*obs;

	obs = ft_calloc(1, sizeof(t_obstacle));
	if (!obs)
		return ;
	obs->next = NULL;
	obs->dist = r_info->ray_distance;
	if (side == 0)
		obs->info.x = st->player.position.y + obs->dist * r_info->ray_dir.y;
	else if (side == 1)
		obs->info.x = st->player.position.x + obs->dist * r_info->ray_dir.x;
	obs->info.x -= floor(obs->info.x);
	obs->info.y = (int)(st->g.main_scene.height / obs->dist);
	obs->half_height = obs->info.y / 2;
	get_obs_info_util(st, obs);
	if (is_wall)
	{
		r_info->wall_start = MAIN_HEIGHT / 2 - obs->half_height;
		r_info->wall_end = MAIN_HEIGHT / 2 + obs->half_height;
	}
	get_obs_tex(st, r_info, obs, side);
	obs->next = r_info->obstacles;
	r_info->obstacles = obs;
}

static void	dda_util(t_app_state *st, t_ray_info *r_info, int *side)
{
	if (r_info->side_dist.x < r_info->side_dist.y)
	{
		r_info->side_dist.x += r_info->delta_dist.x;
		r_info->map.x += r_info->step.x;
		*side = 0;
		r_info->ray_distance = (r_info->map.x - st->player.position.x + (1
					- r_info->step.x) / 2) / r_info->ray_dir.x;
	}
	else
	{
		r_info->side_dist.y += r_info->delta_dist.y;
		r_info->map.y += r_info->step.y;
		*side = 1;
		r_info->ray_distance = (r_info->map.y - st->player.position.y + (1
					- r_info->step.y) / 2) / r_info->ray_dir.y;
	}
}

void	dda(t_app_state *st, t_ray_info *r_info)
{
	int	side;

	while (r_info->wall == NONE_WALL)
	{
		dda_util(st, r_info, &side);
		if (st->g.fog && r_info->ray_distance >= MAX_DISTANCE)
			break ;
		if (r_info->map.x < 0 || r_info->map.x >= st->map->range.x
			|| r_info->map.y < 0 || r_info->map.y >= st->map->range.y)
			break ;
		if (st->map->map[r_info->map.y][r_info->map.x] == '1')
			get_obs_info(st, r_info, side, true);
		else if (st->map->map[r_info->map.y][r_info->map.x] == 'D')
			get_obs_info(st, r_info, side, false);
	}
}
