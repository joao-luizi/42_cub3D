/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 14:10:39 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static inline void	after_wait(t_app_state *st)
{
	pthread_mutex_lock(&st->render_mutex);
	st->threads_done++;
	if (st->threads_done == st->core_count)
		pthread_cond_signal(&st->main_cond);
	pthread_mutex_unlock(&st->render_mutex);
}
static inline bool	pre_wait(t_app_state *st, int index)
{
	pthread_mutex_lock(&st->render_mutex);
	while ((!st->render_ready || !st->thread_can_render[index])
		&& !st->exit_requested)
		pthread_cond_wait(&st->render_cond, &st->render_mutex);
	if (st->exit_requested)
	{
		pthread_mutex_unlock(&st->render_mutex);
		return (false);
	}
	st->thread_can_render[index] = false;
	pthread_mutex_unlock(&st->render_mutex);
	return (true);
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
		if (!pre_wait(st, args->index))
			break ;
		x = args->start_col - 1;
		while (++x < args->end_col)
		{
			initialize_ray(st, &r_info, x);
			setup_initial_step(st, &r_info);
			dda(st, &r_info);
			draw_column(st, &r_info, x);
			free_obstacles(r_info.obstacles);
			r_info.obstacles = NULL;
		}
		render_ceiling_and_floor(st, args->start_col, args->end_col);
		post_process(st, args);
		after_wait(st);
	}
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
	int	i;
	int y;
	int x;
	
	y = -1;
	while(++y < st->g.main_scene.height)
    {
		x = -1;
        while (++x < st->g.main_scene.width)
            draw_pixel(&st->g.main_scene, x, y, 0x000000);
    }
	pthread_mutex_lock(&st->render_mutex);
	st->render_ready = true;
	st->threads_done = 0;
	i = -1;
	while (++i < st->core_count)
		st->thread_can_render[i] = true;
	pthread_cond_broadcast(&st->render_cond);
	pthread_mutex_unlock(&st->render_mutex);
	pthread_mutex_lock(&st->render_mutex);
	while (st->threads_done < st->core_count && !st->exit_requested)
		pthread_cond_wait(&st->main_cond, &st->render_mutex);
	st->render_ready = false;
	pthread_mutex_unlock(&st->render_mutex);
	if (st->exit_requested)
		return ;
}
