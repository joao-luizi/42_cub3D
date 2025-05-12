#include "../../inc/cub3d.h"

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
void	free_config(t_config *cfg)
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
	if (cfg->map.map)
		free_array(cfg->map.map);
}