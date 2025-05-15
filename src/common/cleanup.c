/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 11:27:27 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	free_image(&g->main_scene, mlx);
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
	if (state->mlx)
	{
		free_graphics(&state->g, state->mlx);
		if (state->win)
			mlx_destroy_window(state->mlx, state->win);
		mlx_destroy_display(state->mlx);
		free(state->mlx);
		state->mlx = NULL;
	}
	if (state->map && state->map->map)
	{
		free_array(state->map->map);
		state->map->map = NULL;
	}
	if (state->normal_x)
		free(state->normal_x);
	if (state->column_buffer)
		free(state->column_buffer);
}
