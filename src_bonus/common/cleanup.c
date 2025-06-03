/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 17:52:55 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static void	free_memoization(t_app_state *st)
{
	int	i;
	int	j;

	if (st->player.triangle_points)
	{
		i = -1;
		while (++i < 3)
		{
			j = -1;
			while (++j < MINIMAP_HEIGHT)
				free(st->player.triangle_points[i][j]);
			free(st->player.triangle_points[i]);
		}
		free(st->player.triangle_points);
	}
	if (st->player.fov_points)
	{
		i = -1;
		while (++i < FOV * 2)
			free(st->player.fov_points[i]);
		free(st->player.fov_points);
	}
}

/**
 * @brief Frees the memory allocated for threads.
 *
 * @param state The application state containing the threads and arguments.
 */
static void	free_threads(t_app_state *state)
{
	int	i;

	if (state->threads)
	{
		i = -1;
		while (++i < state->core_count)
			pthread_join(state->threads[i], NULL);
		free(state->threads);
		state->threads = NULL;
	}
}

static void	free_state_aux(t_app_state *state)
{
	if (state->mutex_initialized)
		pthread_mutex_destroy(&state->render_mutex);
	if (state->cond_initialized)
		pthread_cond_destroy(&state->render_cond);
	if (state->main_initialized)
		pthread_cond_destroy(&state->main_cond);
	if (state->map && state->map->map)
		free_array(state->map->map);
	if (state->normal_x)
		free(state->normal_x);
	if (state->normal_y)
		free(state->normal_y);
	if (state->anims)
		free(state->anims);
	if (state->args)
		free(state->args);
	if (state->thread_can_render)
		free(state->thread_can_render);
	free_memoization(state);
}

/**
 * @brief Frees the memory allocated for the application state and its 
 * associated resources.
 *
 * @param state The application state structure to free.
 */
void	free_state(t_app_state *state)
{
	if (!state)
		return ;
	free_threads(state);
	if (state->mlx)
	{
		free_graphics(&state->g, state->mlx);
		if (state->win)
			mlx_destroy_window(state->mlx, state->win);
		mlx_destroy_display(state->mlx);
		free(state->mlx);
		state->mlx = NULL;
	}
	free_state_aux(state);
}
