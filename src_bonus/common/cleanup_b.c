/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:18:48 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:14 by tjorge-l         ###   ########.fr       */
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
