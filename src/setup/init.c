#include "../../inc/cub3d.h"

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
