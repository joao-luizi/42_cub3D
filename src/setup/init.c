#include "../../inc/cub3d.h"

static void	init_player(t_player *player)
{
	if (!player)
		return ;
	player->direction.x = 0;
	player->direction.y = 0;
	player->position.x = -1;
	player->position.y = -1;
	player->plane.x = 0;
	player->plane.y = 0;
	player->speed.linear = 0.04;
	player->speed.angular = 0.02;
	player->shift_pressed = false;
	player->alt_pressed = false;
	player->up_pressed = false;
	player->down_pressed = false;
	player->right_pressed = false;
	player->left_pressed = false;
}

static void	init_image(t_img *img)
{
	if (!img)
		return ;
	img->img_ptr = NULL;
	img->data_addr = NULL;
	img->size_line = 0;
	img->bpp = 0;
	img->endian = 0;
}

static void	init_g(t_graphics *g)
{
	if (!g)
		return ;
	g->floor.red = -1;
	g->floor.green = -1;
	g->floor.blue = -1;
	g->ceil.red = -1;
	g->ceil.green = -1;
	g->ceil.blue = -1;
	init_image(&g->tex_no);
	init_image(&g->tex_so);
	init_image(&g->tex_we);
	init_image(&g->tex_ea);
	init_image(&g->main_scene);
}

void	init_state(t_app_state *state)
{
	if (!state)
		return ;
	state->mlx = NULL;
	state->win = NULL;
	init_map(&state->map);
	init_g(&state->g);
	init_player(&state->player);
}

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->player_position.x = -1;
	map->player_position.y = -1;
	map->player_direction.x = 0;
	map->player_direction.y = 0;
	map->range.x = 0;
	map->range.y = 0;
}
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
	init_map(&cfg->map);
}
