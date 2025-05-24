
#include "../../inc_bonus/cub3d.h"



bool	is_player(t_app_state *st, int x, int y)
{
	int	scale_index;

	if (st->map->minimap_scale == 10)
		scale_index = 0;
	else if (st->map->minimap_scale == 20)
		scale_index = 1;
	else
		scale_index = 2;
	return (st->player.triangle_points[scale_index][y][x]);
}

static inline int	blend_color(int color1, int color2, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = ((color1 >> 16) & 0xFF) * (1 - ratio) + ((color2 >> 16) & 0xFF) * ratio;
	g = ((color1 >> 8) & 0xFF) * (1 - ratio) + ((color2 >> 8) & 0xFF) * ratio;
	b = (color1 & 0xFF) * (1 - ratio) + (color2 & 0xFF) * ratio;
	return ((r << 16) | (g << 8) | b);
}

bool	is_local_wall(t_app_state *st, int x, int y)
{
	int		map_x;
	int		map_y;
	double	angle;

	angle = atan2(st->player.direction.y, st->player.direction.x) + M_PI_2;
	map_x = (int)(st->player.position.x + (cos(angle) * ((x - MINIMAP_WIDTH / 2)
					/ (double)st->map->minimap_scale) - sin(angle) * ((y
						- MINIMAP_HEIGHT / 2)
					/ (double)st->map->minimap_scale)));
	map_y = (int)(st->player.position.y + (sin(angle) * ((x - MINIMAP_WIDTH / 2)
					/ (double)st->map->minimap_scale) + cos(angle) * ((y
						- MINIMAP_HEIGHT / 2)
					/ (double)st->map->minimap_scale)));
	if (map_x < 0 || map_x >= st->map->range.x || map_y < 0
		|| map_y >= st->map->range.y)
		return (false);
	return (st->map->map[map_y][map_x] == '1');
}
int get_local_wall_color(t_app_state *st, int x, int y)
{
	int		map_x;
	int		map_y;
	double	angle;

	angle = atan2(st->player.direction.y, st->player.direction.x) + M_PI_2;
	map_x = (int)(st->player.position.x + (cos(angle) * ((x - MINIMAP_WIDTH / 2)
					/ (double)st->map->minimap_scale) - sin(angle) * ((y
						- MINIMAP_HEIGHT / 2)
					/ (double)st->map->minimap_scale)));
	map_y = (int)(st->player.position.y + (sin(angle) * ((x - MINIMAP_WIDTH / 2)
					/ (double)st->map->minimap_scale) + cos(angle) * ((y
						- MINIMAP_HEIGHT / 2)
					/ (double)st->map->minimap_scale)));
	if (map_x < 0 || map_x >= st->map->range.x || map_y < 0
		|| map_y >= st->map->range.y)
		return (0xFF00FF);
	if (st->map->map[map_y][map_x] == '1')
		return (0xFFFFFF);
	if (st->map->map[map_y][map_x] == 'D')
	{
		t_anim_slot	*door_anim;
		door_anim = find_door_anim(st, map_x, map_y);
		if (door_anim && door_anim->current_frame == 0)
			return (0x00FF00);
	}
	return (0x808080);
}


static inline int	get_local_color(int x)
{
	double	blend_ratio;
	int		color;

	if (x > FOV_D / 4)
	{
		blend_ratio = (double)(x - FOV_D / 4) / (FOV_D - FOV_D / 4);
		color = blend_color(0x45D4FF, 0x808080, blend_ratio);
	}
	else
		color = 0x45D4FF;
	return (color);
}

int	get_color(t_app_state *st, int x, int y)
{
	if (is_player(st, x, y))
		return (0xFF0000);
	else
		return (get_local_wall_color(st, x, y));
}
static inline void	render_fov(t_app_state *st, t_args *args)
{
	int	y;
	int	x;
	int	color;

	y = -1;
	while (++y < FOV * 2)
	{
		x = -1;
		while (++x < FOV_D)
		{
			if (x >= args->start_col && x <= args->end_col)
			{
				color = get_local_wall_color(st, st->player.fov_points[y][x].x,
						st->player.fov_points[y][x].y);
				if (color != 0x808080)
					break;
				//if (is_local_wall(st, st->player.fov_points[y][x].x,
				//		st->player.fov_points[y][x].y))
			//		break ;
				if (!is_player(st, st->player.fov_points[y][x].x,
						st->player.fov_points[y][x].y))
				{
					color = get_local_color(x);
					draw_pixel(&st->g.main_scene, st->player.fov_points[y][x].x,
						st->player.fov_points[y][x].y, color);
				}
			}
		}
	}
}

void	render_minimap(t_app_state *st, t_args *args)
{
	int y;
	int x;
	int color;
	if (!st->g.minimap)
		return ;
	if (MINIMAP_X + MINIMAP_WIDTH < args->start_col || MINIMAP_X > args->end_col)
		return ;
	y = -1;
	while (++y < MINIMAP_HEIGHT)
	{
		x = -1;
		while (++x < MINIMAP_WIDTH)
		{
			
			if (x >= args->start_col && x < args->end_col)
            {
				color = get_color(st, x, y);
				if (color != 0xFF00FF)
                	draw_pixel(&st->g.main_scene, x, y, get_color(st, x,
						y));
            }
				
		}
	}
	render_fov(st, args);
}