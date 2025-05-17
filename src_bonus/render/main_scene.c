/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/17 18:30:02 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void	*raycast_routine(void *arg)
{
	t_args		*args;
	t_app_state	*st;
	int			x;

	args = (t_args *)arg;
	st = args->st;
	while (true)
	{
		pthread_mutex_lock(&st->render_mutex);
        while (!st->render_ready)
            pthread_cond_wait(&st->render_cond, &st->render_mutex);
        pthread_mutex_unlock(&st->render_mutex);
		x = args->start_col;
		printf("Thread %ld: Column Start %d Column End %d\n", pthread_self(), x, args->end_col);
		while (x < args->end_col)
		{
			// init_raycast
			// step_routine
			// get_wall
			// draw_column
			x++;
		}
		pthread_mutex_lock(&st->render_mutex);
        st->threads_done++;
        if (st->threads_done == st->core_count)
        {
            st->render_ready = false;
            pthread_cond_signal(&st->render_cond);
        }
        pthread_mutex_unlock(&st->render_mutex);
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
	
    pthread_mutex_lock(&st->render_mutex);
    st->render_ready = true;
    st->threads_done = 0;
    pthread_cond_broadcast(&st->render_cond);
    pthread_mutex_unlock(&st->render_mutex);

   
    pthread_mutex_lock(&st->render_mutex);
    while (st->threads_done < st->core_count)
        pthread_cond_wait(&st->render_cond, &st->render_mutex);
    pthread_mutex_unlock(&st->render_mutex);
}
