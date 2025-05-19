/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/19 19:58:04 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"
#include <string.h>
static inline void	after_wait(t_app_state *st)
{
	pthread_mutex_lock(&st->render_mutex);
	st->threads_done++;
    printf("Thread signaled done, threads_done = %d\n", st->threads_done);
	if (st->threads_done == st->core_count)
	{
		st->render_ready = false;
		pthread_cond_signal(&st->render_cond);
	}
	pthread_mutex_unlock(&st->render_mutex);
}
static inline bool	pre_wait(t_app_state *st)
{
	pthread_mutex_lock(&st->render_mutex);
	while (!st->render_ready && !st->exit_requested)
		pthread_cond_wait(&st->render_cond, &st->render_mutex);
	if (st->exit_requested)
	{
		pthread_mutex_unlock(&st->render_mutex);
		return (false);
	}
	pthread_mutex_unlock(&st->render_mutex);
	return (true);
}

static inline void	setup_initial_step(t_app_state *st, t_ray_info *r_info)
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
static inline void	initialize_ray(t_app_state *st, t_ray_info *r_info, int x)
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

static void	free_obstacles(t_obstacle *head)
{
	t_obstacle	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

static inline void	get_wall_tex(t_ray_info *r_info, int side)
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
}
static inline void	get_obs_tex(t_app_state *st, t_ray_info *r_info,
		t_obstacle *obs, int side)
{
	t_anim_slot	*anim;

	if (st->map->map[r_info->map.y][r_info->map.x] == '1')
	{
		get_wall_tex(r_info, side);
		if (r_info->wall == NO_WALL)
			obs->current_tex = &st->g.tex_no;
		else if (r_info->wall == SO_WALL)
        {
			obs->current_tex = &st->g.tex_so;
            obs->flip_texture = true;
        }
		else if (r_info->wall == EA_WALL)
			obs->current_tex = &st->g.tex_ea;
		else if (r_info->wall == WE_WALL)
        {
			obs->current_tex = &st->g.tex_we;
            obs->flip_texture = true;
        }
		else
			obs->current_tex = NULL;
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
	get_obs_tex(st, r_info, obs, side);
	obs->next = r_info->obstacles;
	r_info->obstacles = obs;
}

static inline void	dda(t_app_state *st, t_ray_info *r_info)
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

static inline void	draw_column(t_app_state *st, t_ray_info *r_info, int x)
{
    t_obstacle    *obs;
    int             obs_w[2];
    int y;
    int color;
    obs = r_info->obstacles;
    //while (obs)
    if (obs)
    {
        obs_w[0] = st->g.main_scene.half_height - obs->half_height;
        obs_w[1] = obs_w[0] + obs->info.y;
        y = obs_w[0];
        if (y < 0)
            y = -1;
        while (++y <= obs_w[1] && y < st->g.main_scene.height)
        {
            color = get_obs_color(obs, y, obs_w[0]);
            if (color != 0xFF00FF)
                draw_pixel(&st->g.main_scene, x, y, color);
        }   
    }
}
void	*raycast_routine(void *arg)
{
	t_args		*args;
	t_app_state	*st;
	t_ray_info	r_info;
	int			x;

	args = (t_args *)arg;
	st = args->st;
	while (true)
	{
        if (!pre_wait(st))
        break ;
		render_ceiling_and_floor(st, args->start_col, args->end_col);
		x = args->start_col - 1;
        //printf("Thread printing %d to %d cols\n", x + 1, args->end_col - 1);
		while (++x < args->end_col)
		{
			initialize_ray(st, &r_info, x);
			setup_initial_step(st, &r_info);
			dda(st, &r_info);
			draw_column(st, &r_info, x);
			free_obstacles(r_info.obstacles);
			r_info.obstacles = NULL;
		}
		after_wait(st);
	}
	printf("Thread exiting...\n");
	return (NULL);
}
/**
 * @brief Renders the main scene by casting rays and drawing the
 * corresponding wall slices.
 *
 * @param st The application state containing the game's data.
 */
void	render_main_scene(t_app_state *st)
{
    
	// Signal threads to start rendering
	pthread_mutex_lock(&st->render_mutex);
	st->render_ready = true;
	st->threads_done = 0;
	pthread_cond_broadcast(&st->render_cond);
	pthread_mutex_unlock(&st->render_mutex);
	// Wait for threads to finish or exit if requested
    printf("Main thread: waiting for threads to finish %ld...\n", st->core_count);
	pthread_mutex_lock(&st->render_mutex);
	while (st->threads_done < st->core_count && !st->exit_requested)
		pthread_cond_wait(&st->render_cond, &st->render_mutex);
	pthread_mutex_unlock(&st->render_mutex);
    printf("Main thread: all threads finished!\n");
    memcpy(st->g.buffer.data_addr, st->g.main_scene.data_addr,
           st->g.main_scene.width * st->g.main_scene.height * sizeof(int));
	// If exit_requested is true, handle cleanup or exit logic if needed
	if (st->exit_requested)
	{
		printf("Render main scene exiting early due to exit request.\n");
		return ;
	}
}
