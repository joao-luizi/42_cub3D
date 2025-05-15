/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:53 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 23:54:29 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Initializes the player structure with default values.
 * 
 * @param player The player structure to initialize.
 */
static void	init_player(t_player *player)
{
	if (!player)
		return ;
	player->direction.x = 0;
	player->direction.y = 0;
	player->position.x = -1;
	player->position.y = -1;
	player->rotation_factor_pos.x = cos(PLAYER_ROT_SPEED);
	player->rotation_factor_pos.y = sin(PLAYER_ROT_SPEED);
	player->rotation_factor_neg.x = cos(-PLAYER_ROT_SPEED);
	player->rotation_factor_neg.y = sin(-PLAYER_ROT_SPEED);
	player->plane.x = 0;
	player->plane.y = 0;
	player->speed.linear = PLAYER_MOV_SPEED;
	player->speed.angular = PLAYER_ROT_SPEED;
	player->shift_pressed = false;
	player->alt_pressed = false;
	player->up_pressed = false;
	player->down_pressed = false;
	player->right_pressed = false;
	player->left_pressed = false;
	player->turn_left_pressed = false;
	player->turn_right_pressed = false;
}

/**
 * @brief Initializes the image structure with default values.
 * 
 * @param img The image structure to initialize.
 */
static void	init_image(t_img *img)
{
	if (!img)
		return ;
	img->img_ptr = NULL;
	img->data_addr = NULL;
	img->size_line = 0;
	img->bpp = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
	img->half_height = 0;
	img->half_width = 0;
}

/**
 * @brief Initializes the graphics structure with default values.
 * 
 * @param g The graphics structure to initialize.
 */
static void	init_g(t_graphics *g)
{
	if (!g)
		return ;
	g->fps = false;
	init_image(&g->tex_fl);
	init_image(&g->tex_cl);
	init_image(&g->tex_no);
	init_image(&g->tex_so);
	init_image(&g->tex_we);
	init_image(&g->tex_ea);
	init_image(&g->main_scene);
	g->door_anim = NULL;
	g->face_anim = NULL;
}

/**
 * @brief Initializes the application state structure with default 
 * values.
 * 
 * @param state The application state structure to initialize.
 */
void	init_state(t_app_state *state)
{
	if (!state)
		return ;
	state->mlx = NULL;
	state->win = NULL;
	state->map = NULL;
	state->normal_x = NULL;
	state->column_buffer = NULL;
	init_g(&state->g);
	init_player(&state->player);
}

/**
 * @brief Initializes the configuration structure with default values.
 * 
 * @param cfg The configuration structure to initialize.
 */
void	init_config(t_config *cfg)
{
	if (!cfg)
		return ;
	cfg->normal_file_path = NULL;
	cfg->no_tex = NULL;
	cfg->so_tex = NULL;
	cfg->we_tex = NULL;
	cfg->ea_tex = NULL;
	cfg->map.map = NULL;
	cfg->cl_tex = NULL;
	cfg->fl_tex = NULL;
	cfg->map.map = NULL;
	cfg->door_anim = NULL;
	cfg->face_anim = NULL;
	cfg->map.player_position.x = -1;
	cfg->map.player_position.y = -1;
	cfg->map.player_direction.x = 0;
	cfg->map.player_direction.y = 0;
	cfg->map.range.x = 0;
	cfg->map.range.y = 0;
}
