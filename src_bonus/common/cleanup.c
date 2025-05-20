/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 13:34:39 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Frees a null-terminated array of strings.
 *
 * @param arr The array of strings to free.
 */
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/**
 * @brief Frees the memory allocated for the configuration structure.
 *
 * @param cfg The configuration structure to free.
 * @param free_map A boolean indicating whether to free the map inside the 
 configuration.
 */
void	free_config(t_config *cfg, bool free_map)
{
	if (!cfg)
		return ;
	if (cfg->normal_file_path)
		free(cfg->normal_file_path);
	if (cfg->no_tex)
		free(cfg->no_tex);
	if (cfg->so_tex)
		free(cfg->so_tex);
	if (cfg->we_tex)
		free(cfg->we_tex);
	if (cfg->ea_tex)
		free(cfg->ea_tex);
	if (cfg->cl_tex)
		free(cfg->cl_tex);
	if (cfg->fl_tex)
		free(cfg->fl_tex);
	if (cfg->door_anim)
		free(cfg->door_anim);
	if (cfg->face_anim)
		free(cfg->face_anim);
	if (free_map && cfg->map.map)
	{
		free_array(cfg->map.map);
		cfg->map.map = NULL;
	}
}

/**
 * @brief Frees the memory allocated for an image structure and destroys 
 * the image.
 *
 * @param img The image structure to free.
 * @param mlx The MiniLibX instance used to destroy the image.
 */
static void	free_image(t_img *img, void *mlx)
{
	if (!img)
		return ;
	if (img->img_ptr)
		mlx_destroy_image(mlx, img->img_ptr);
	img->img_ptr = NULL;
	img->data_addr = NULL;
}

static void free_anim(t_anim *anim, void *mlx)
{
	int i;
	
	i = -1;
	while (++i < 4)
	{
		if (anim[i].frame.img_ptr)
			free_image(&anim[i].frame, mlx);
	}
	free(anim);
}
/**
 * @brief Frees the memory allocated for graphics-related resources.
 *
 * @param g The graphics structure to free.
 * @param mlx The MiniLibX instance used to destroy the graphics resources.
 */
static void	free_graphics(t_graphics *g, void *mlx)
{
	if (!g)
		return ;
	free_image(&g->tex_no, mlx);
	free_image(&g->tex_so, mlx);
	free_image(&g->tex_we, mlx);
	free_image(&g->tex_ea, mlx);
	free_image(&g->tex_cl, mlx);
	free_image(&g->tex_fl, mlx);
	free_image(&g->main_scene, mlx);
	if (g->door_anim)
		free_anim(g->door_anim, mlx);
	if (g->face_anim)
		free_anim(g->face_anim, mlx);
}

/**
 * @brief Frees the memory allocated for threads.
 *
 * @param state The application state containing the threads and arguments.
 */
static void free_threads(t_app_state *state)
{
	int i;

    if (state->threads)
    {
		i = -1;
		while (++i < state->core_count)
		{
            pthread_join(state->threads[i], NULL);
        }

        free(state->threads);
        state->threads = NULL;
    }
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
	if (state->anims)
		free(state->anims);
	if (state->args)
		free(state->args);
	if (state->thread_can_render)
		free(state->thread_can_render);
}

void	free_obstacles(t_obstacle *head)
{
	t_obstacle	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}