/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vertical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/21 12:38:42 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void	draw_column(t_app_state *st, t_ray_info *r_info, int x)
{
	t_obstacle	*obs;
	int			obs_w[2];
	int			y;
	int			color;

	obs = r_info->obstacles;
	while (obs)
	{
		obs_w[0] = st->g.main_scene.half_height - obs->half_height;
		obs_w[1] = obs_w[0] + obs->info.y;
		y = obs_w[0];
		if (y < 0)
			y = -1;
		while (++y <= obs_w[1] && y < st->g.main_scene.height)
		{
			color = get_obs_color(obs, y, obs_w[0], 0.0f);
			if (color != 0xFF00FF)
			{
				color = get_obs_color(obs, y, obs_w[0], obs->blending_factor);
				draw_pixel(&st->g.main_scene, x, y, color);
			}
		}
		obs = obs->next;
	}
}

void	setup_initial_step(t_app_state *st, t_ray_info *r_info)
{
	if (r_info->ray_dir.x < 0)
	{
		r_info->step.x = -1;
		r_info->side_dist.x = (st->player.position.x - r_info->map.x)
			* r_info->delta_dist.x;
	}
	else
	{
		r_info->step.x = 1;
		r_info->side_dist.x = (r_info->map.x + 1.0 - st->player.position.x)
			* r_info->delta_dist.x;
	}
	if (r_info->ray_dir.y < 0)
	{
		r_info->step.y = -1;
		r_info->side_dist.y = (st->player.position.y - r_info->map.y)
			* r_info->delta_dist.y;
	}
	else
	{
		r_info->step.y = 1;
		r_info->side_dist.y = (r_info->map.y + 1.0 - st->player.position.y)
			* r_info->delta_dist.y;
	}
}

void	initialize_ray(t_app_state *st, t_ray_info *r_info, int x)
{
	r_info->ray_dir.x = st->player.direction.x + st->player.plane.x
		* st->normal_x[x];
	r_info->ray_dir.y = st->player.direction.y + st->player.plane.y
		* st->normal_x[x];
	r_info->map.x = (int)st->player.position.x;
	r_info->map.y = (int)st->player.position.y;
	r_info->delta_dist.x = fabs(1 / r_info->ray_dir.x);
	r_info->delta_dist.y = fabs(1 / r_info->ray_dir.y);
	r_info->obstacles = NULL;
	r_info->wall = NONE_WALL;
	r_info->wall_start = -1;
	r_info->wall_end = -1;
	r_info->ray_distance = 0;
}
