/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:43:48 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 11:51:04 by tjorge-l         ###   ########.fr       */
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

static void	raycast_util(t_app_state *st, t_args *args)
{
	int			x;
	t_ray_info	r_info;

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

void	*raycast_routine(void *arg)
{
	t_args		*args;
	t_app_state	*st;

	args = (t_args *)arg;
	st = args->st;
	while (true)
	{
		if (!pre_wait(st, args->index))
			break ;
		raycast_util(st, args);
	}
	return (NULL);
}
