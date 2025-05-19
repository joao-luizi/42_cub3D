/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/19 19:48:44 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Initializes the ray's step and side distances based on its 
 * direction.
 * 
 * @param st The application state containing the player's data.
 * @param r_info The ray information structure to initialize.
 */
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
static inline void get_wall_tex(t_wall type, t_obstacle *obs, t_app_state *st)
{
	if (type == NO_WALL)
		obs->current_tex = &st->g.tex_no;
	else if (type == SO_WALL)
		obs->current_tex = &st->g.tex_so;
	else if (type == EA_WALL)
		obs->current_tex = &st->g.tex_ea;
	else if (type == WE_WALL)
		obs->current_tex = &st->g.tex_we;
}
static inline void get_obs_tex(t_app_state *st, t_ray_info *r_info, t_obstacle *obs, int side)
{
	t_anim_slot *anim;
	
	if (st->map->map[r_info->map.y][r_info->map.x] == '1')
	{
		if (side == 0)
		{
			if (r_info->step.x == -1)
				r_info->wall = WE_WALL;
			else
				r_info->wall = EA_WALL;
		}
		else if (side == 1)
		{
			if (r_info->step.y == -1)
				r_info->wall = NO_WALL;
			else
				r_info->wall = SO_WALL;
		}
		get_wall_tex(r_info->wall, obs, st);
	}
	else
	{
		anim = find_door_anim(st, r_info->map.x, r_info->map.y);
		if (anim)
			obs->current_tex = &anim->anim_info[anim->current_frame].frame;
		else
			obs->current_tex = NULL;
	}
}
static inline void	get_door_info(t_app_state *st, t_ray_info *r_info, int side)
{
	t_obstacle *obstacle;
	
	if (side == 0)
	{
		obstacle->dist = (r_info->map.x - st->player.position.x + (1
					- r_info->step.x) / 2) / r_info->ray_dir.x;
		obstacle->info.x = st->player.position.y + obstacle->dist
			* r_info->ray_dir.y;
	}
	else if (side == 1)
	{
		obstacle->dist = (r_info->map.y - st->player.position.y + (1
					- r_info->step.y) / 2) / r_info->ray_dir.y;
		obstacle->info.x = st->player.position.x + obstacle->dist
			* r_info->ray_dir.x;
	}
	obstacle->info.x -= floor(obstacle->info.x); 
	obstacle->info.y = (int)(st->g.main_scene.height / obstacle->dist);
	obstacle->half_height = obstacle->info.y / 2;
}


/**
 * @brief Traces the ray through the map to find the first wall it 
 * intersects.
 * 
 * @param st The application state containing the player's data.
 * @param r_info The ray information structure to update.
 */
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
		else if (st->map->map[r_info->map.y][r_info->map.x] == 'D')
			get_door_info(st, r_info, side);
	}
}

/**
 * @brief Draws a vertical column of pixels representing a wall slice on 
 * the screen.
 * 
 * @param st The application state containing the game's data.
 * @param r_info The ray information structure containing wall details.
 * @param x The x-coordinate of the column to draw.
 */
/* static inline void	draw_column(t_app_state *st, t_ray_info *r_info, int x)
{
	int		y;
	int		wall[2];
	int		door[2];
	t_img	*wall_tex;
	int		tex_i;

	wall[0] = st->g.main_scene.half_height - r_info->wall_half;
	wall[1] = wall[0] + r_info->wall_info.y;
	if (r_info->door_dist >= 0)
	{
		door[0] = st->g.main_scene.half_height - r_info->door_half;
		door[1] = door[0] + r_info->door_info.y;
		precompute_door(st->door_buffer, door, r_info, r_info->door_tex);
	}
	get_wall_tex(&wall_tex, r_info->wall, st);
	precompute_column(st->column_buffer, wall, r_info, wall_tex);
	y = -1;
	while (++y < wall[0])
		draw_pixel(&st->g.main_scene, x, y, 0x00FF00);
	tex_i = 0;
	if (wall[0] == wall[1])
	{
		draw_pixel(&st->g.main_scene, x, y, 0x00FF00);
		draw_pixel(&st->g.main_scene, x, y + 1, 0x0000FF);
	}
	while (++y <= wall[1] && y < st->g.main_scene.height)
	{
		draw_pixel(&st->g.main_scene, x, y, st->column_buffer[tex_i]);
		tex_i++;
	}
	while (++y < st->g.main_scene.height)
		draw_pixel(&st->g.main_scene, x, y, 0x0000FF);
	if (r_info->door_dist >= 0)
	{
		y = door[0];
		if (y < 0)
			y = 0;
		tex_i = 0;
		while (y <= door[1] && y < st->g.main_scene.height)
		{
			if (st->door_buffer[tex_i] != 0xFF00FF)
				draw_pixel(&st->g.main_scene, x, y, st->door_buffer[tex_i]);
			tex_i++;
			y++;
		}
	}
} */

/**
 * @brief Renders the main scene by casting rays and drawing the 
 * corresponding wall slices.
 * 
 * @param st The application state containing the game's data.
 */
/* void	render_main_scene(t_app_state *st)
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
		ray_info.door_info.x = -1.0;
		ray_info.door_info.y = -1.0;
		ray_info.door_half = -1;
		ray_info.door_dist = -1;
		ray_info.door_tex = NULL;
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
} */
