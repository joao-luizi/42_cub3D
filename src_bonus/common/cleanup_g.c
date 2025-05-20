/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_g.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 15:18:34 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"



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
void	free_graphics(t_graphics *g, void *mlx)
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
