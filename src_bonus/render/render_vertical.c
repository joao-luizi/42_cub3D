/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vertical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 16:52:32 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static inline void	get_obs_info(t_app_state *st, t_ray_info *r_info, int side)
{
	t_obstacle	*obs;

	obs = ft_calloc(1, sizeof(t_obstacle));
	if (!obs)
		return ;
	obs->next = NULL;
	if (side == 0)
	{
		obs->dist = (r_info->map.x - st->player.position.x + (1
					- r_info->step.x) / 2) / r_info->ray_dir.x;
		obs->info.x = st->player.position.y + obs->dist * r_info->ray_dir.y;
	}
	else if (side == 1)
	{
		obs->dist = (r_info->map.y - st->player.position.y + (1
					- r_info->step.y) / 2) / r_info->ray_dir.y;
		obs->info.x = st->player.position.x + obs->dist * r_info->ray_dir.x;
	}
	obs->info.x -= floor(obs->info.x);
	obs->info.y = (int)(st->g.main_scene.height / obs->dist);
	obs->half_height = obs->info.y / 2;
	if (st->g.fog == true)
	{
		if (obs->dist >= MAX_DISTANCE)
			obs->blending_factor = 1.0f;
		else
			obs->blending_factor = obs->dist / MAX_DISTANCE;
	}
	else
		obs->blending_factor = 0.0f;
	get_obs_tex(st, r_info, obs, side);
	obs->next = r_info->obstacles;
	r_info->obstacles = obs;
}

void	dda(t_app_state *st, t_ray_info *r_info)
{
	int	side;

	while (r_info->wall == NONE_WALL)
	{
		if (r_info->side_dist.x < r_info->side_dist.y)
		{
			r_info->side_dist.x += r_info->delta_dist.x;
			r_info->map.x += r_info->step.x;
			side = 0;
		}
		else
		{
			r_info->side_dist.y += r_info->delta_dist.y;
			r_info->map.y += r_info->step.y;
			side = 1;
		}
		if (r_info->map.x < 0 || r_info->map.x >= st->map->range.x
			|| r_info->map.y < 0 || r_info->map.y >= st->map->range.y)
			break ;
		if (st->map->map[r_info->map.y][r_info->map.x] == '1'
			|| st->map->map[r_info->map.y][r_info->map.x] == 'D')
			get_obs_info(st, r_info, side);
	}
}

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
			// Get the original color from the texture
            color = get_obs_color(obs, y, obs_w[0], 0.0f); // Pass 0.0f to avoid blending here

            // Check for transparency (MAGENTA)
            if (color != 0xFF00FF)
            {
                // Apply blending only to solid colors
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
	
}
