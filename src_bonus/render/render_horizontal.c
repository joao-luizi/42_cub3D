/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_horizontal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/24 14:24:04 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static inline void	paint_pixels(t_app_state *st, t_point screen,
	t_vector ray_dir, int idy)
{
	t_vector	ceiling;
	t_point		tex;
	double		denom;
	double		distance;

	denom = ray_dir.x * st->player.direction.x + ray_dir.y
		* st->player.direction.y;
	ceiling.x = st->player.position.x + (st->normal_y[idy] / denom) * ray_dir.x;
	ceiling.y = st->player.position.y + (st->normal_y[idy] / denom) * ray_dir.y;
	tex.x = (int)(ceiling.x * st->g.tex_cl.width) % st->g.tex_cl.width;
	tex.y = (int)(ceiling.y * st->g.tex_cl.height) % st->g.tex_cl.height;
	if (st->g.fog)
	{
		distance = sqrt(pow(ceiling.x - st->player.position.x, 2)
				+ pow(ceiling.y - st->player.position.y, 2));
	}
	else
		distance = 0;
	draw_pixel(&st->g.main_scene, screen.x, MAIN_HEIGHT - screen.y - 1,
		get_pixel_color(&st->g.tex_cl, tex.x, tex.y, distance / MAX_DISTANCE));
	draw_pixel(&st->g.main_scene, screen.x, screen.y,
		get_pixel_color(&st->g.tex_fl, tex.x, tex.y, distance / MAX_DISTANCE));
}

static inline void	calculate_ray_direction(t_vector *ray_dir,
			t_app_state *st, t_point screen, double *denom)
{
	ray_dir->x = st->player.direction.x + st->player.plane.x
		*st->normal_x[screen.x];
	ray_dir->y = st->player.direction.y + st->player.plane.y
		*st->normal_x[screen.x];
	*denom = ray_dir->x * st->player.direction.x + ray_dir->y
		*st->player.direction.y;
}

static void	render_ceiling_floor_util(t_app_state *st, t_point *screen,
										int end_x, int *idy)
{
	double		denom;
	t_vector	ray_dir;

	while (screen->x < end_x)
	{
		if (get_pixel_color(&st->g.main_scene,
				screen->x, screen->y, 0) != 0x000000)
		{
			screen->x++;
			continue ;
		}
		calculate_ray_direction(&ray_dir, st, *screen, &denom);
		if (denom == 0)
		{
			screen->x++;
			continue ;
		}
		paint_pixels(st, *screen, ray_dir, (*idy));
		screen->x++;
	}
	screen->y++;
	(*idy)++;
}

void	render_ceiling_and_floor(t_app_state *st, int start_x, int end_x)
{
	int			idy;
	t_point		screen;

	screen.y = MAIN_HEIGHT / 2;
	idy = 0;
	while (screen.y < MAIN_HEIGHT)
	{
		screen.x = start_x;
		render_ceiling_floor_util(st, &screen, end_x, &idy);
	}
}
