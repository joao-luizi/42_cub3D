/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/24 14:20:53 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static void	render_main_scene_util(t_app_state *st)
{
	int	y;
	int	x;

	y = -1;
	while (++y < st->g.main_scene.height)
	{
		x = -1;
		while (++x < st->g.main_scene.width)
			draw_pixel(&st->g.main_scene, x, y, 0x000000);
	}
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

	render_main_scene_util(st);
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
