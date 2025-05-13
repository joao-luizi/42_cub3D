/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/13 18:25:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static inline void	initialize_ray(t_app_state *st, t_ray_info *r_info)
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

static inline void	get_wall_info(t_app_state *st, t_ray_info *r_info, int side)
{
	if (side == 0)
	{
		if (r_info->step.x == -1)
			r_info->wall = WE_WALL;
		else
			r_info->wall = EA_WALL;
		r_info->wall_dist = (r_info->map.x - st->player.position.x + (1
					- r_info->step.x) / 2) / r_info->ray_dir.x;
		r_info->wall_info.x = st->player.position.y + r_info->wall_dist
			* r_info->ray_dir.y;
	}
	else if (side == 1)
	{
		if (r_info->step.y == -1)
			r_info->wall = NO_WALL;
		else
			r_info->wall = SO_WALL;
		r_info->wall_dist = (r_info->map.y - st->player.position.y + (1
					- r_info->step.y) / 2) / r_info->ray_dir.y;
		r_info->wall_info.x = st->player.position.x + r_info->wall_dist
			* r_info->ray_dir.x;
	}
	r_info->wall_info.x -= floor(r_info->wall_info.x);
	r_info->wall_info.y = (int)(st->g.main_scene.height / r_info->wall_dist);
	r_info->wall_half = r_info->wall_info.y / 2;
}

static inline void	get_wall(t_app_state *st, t_ray_info *r_info)
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
		if (st->map->map[r_info->map.y][r_info->map.x] == '1')
			get_wall_info(st, r_info, side);
	}
}

static inline void	draw_column(t_app_state *st, t_ray_info *r_info, int x)
{
	int		y;
	int		wall[2];
	t_img	*wall_tex;

	wall_tex = NULL;
	wall[0] = st->g.main_scene.half_height - r_info->wall_half;
	wall[1] = wall[0] + r_info->wall_info.y;
	y = -1;
	while (++y < wall[0])
		draw_pixel(&st->g.main_scene, x, y, st->g.ceil);
	while (++y <= wall[1] && y < st->g.main_scene.height)
	{
		if (r_info->wall == NO_WALL)
			wall_tex = &st->g.tex_no;
		else if (r_info->wall == SO_WALL)
			wall_tex = &st->g.tex_so;
		else if (r_info->wall == WE_WALL)
			wall_tex = &st->g.tex_we;
		else if (r_info->wall == EA_WALL)
			wall_tex = &st->g.tex_ea;
		draw_pixel(&st->g.main_scene, x, y, get_tex_color(wall_tex,
				r_info, y, wall[0]));
	}
	while (++y < st->g.main_scene.height)
		draw_pixel(&st->g.main_scene, x, y, st->g.floor);
}

void	render_main_scene(t_app_state *st)
{
	int			x;
	t_ray_info	ray_info;

	x = -1;
	while (++x < st->g.main_scene.width)
	{
		ray_info.wall = NONE_WALL;
		ray_info.wall_info.x = 0;
		ray_info.wall_info.y = 0;
		ray_info.wall_half = 0;
		ray_info.ray_dir.x = st->player.direction.x + st->player.plane.x
			* st->normal_x[x];
		ray_info.ray_dir.y = st->player.direction.y + st->player.plane.y
			* st->normal_x[x];
		ray_info.map.x = (int)st->player.position.x;
		ray_info.map.y = (int)st->player.position.y;
		ray_info.delta_dist.x = fabs(1 / ray_info.ray_dir.x);
		ray_info.delta_dist.y = fabs(1 / ray_info.ray_dir.y);
		initialize_ray(st, &ray_info);
		get_wall(st, &ray_info);
		draw_column(st, &ray_info, x);
	}
}
