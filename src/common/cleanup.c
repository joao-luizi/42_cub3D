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

static void	free_image(t_img *img, void *mlx)
{
	if (!img)
		return;
	if (img->img_ptr)
		mlx_destroy_image(mlx, img->img_ptr);
	img->img_ptr = NULL;
	img->data_addr = NULL;
}

static void	free_graphics(t_graphics *g, void *mlx)
{
	if (!g)
		return;
	free_image(&g->tex_no, mlx);
	free_image(&g->tex_so, mlx);
	free_image(&g->tex_we, mlx);
	free_image(&g->tex_ea, mlx);
	free_image(&g->main_scene, mlx);
}

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
}


