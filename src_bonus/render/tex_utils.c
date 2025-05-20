#include "../../inc_bonus/cub3d.h"

static inline void	get_anim_tex(t_app_state *st, t_ray_info *r_info,
		t_obstacle *obs)
{
	t_anim_slot *anim;

	anim = find_door_anim(st, r_info->map.x, r_info->map.y);
	if (anim)
		obs->current_tex = &anim->anim_info[anim->current_frame].frame;
	else
		obs->current_tex = NULL;
}
static inline void	get_wall_tex(t_ray_info *r_info, int side)
{
	if (side == 0)
	{
		if (r_info->step.x == -1)
			r_info->wall = WE_WALL;
		else
			r_info->wall = EA_WALL;
	}
	else if (side == 1)
	{
		if (r_info->step.y == -1)
			r_info->wall = NO_WALL;
		else
			r_info->wall = SO_WALL;
	}
}
void	get_obs_tex(t_app_state *st, t_ray_info *r_info, t_obstacle *obs,
		int side)
{
	if (st->map->map[r_info->map.y][r_info->map.x] == '1')
	{
		get_wall_tex(r_info, side);
		if (r_info->wall == NO_WALL)
			obs->current_tex = &st->g.tex_no;
		else if (r_info->wall == SO_WALL)
		{
			obs->current_tex = &st->g.tex_so;
			obs->flip_texture = true;
		}
		else if (r_info->wall == EA_WALL)
			obs->current_tex = &st->g.tex_ea;
		else if (r_info->wall == WE_WALL)
		{
			obs->current_tex = &st->g.tex_we;
			obs->flip_texture = true;
		}
		else
			obs->current_tex = NULL;
	}
	else
		get_anim_tex(st, r_info, obs);
}
