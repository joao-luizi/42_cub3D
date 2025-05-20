/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_horizontal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 14:16:58 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static int	get_pixel_color(t_img *img, int tex_x, int tex_y)
{
	int	pixel;

	pixel = *(int *)(img->data_addr + (tex_y * img->size_line + tex_x
				* (img->bpp / 8)));
	return (pixel);
}

static inline void	paint_pixels(t_app_state *st, t_point screen,
		t_vector ray_dir, int idy)
{
	t_vector	floor;
	t_point		tex;
	double		denom;

	denom = ray_dir.x * st->player.direction.x + ray_dir.y
		* st->player.direction.y;
	floor.x = st->player.position.x + (st->normal_y[idy] / denom) * ray_dir.x;
	floor.y = st->player.position.y + (st->normal_y[idy] / denom) * ray_dir.y;
	tex.x = (int)(floor.x * st->g.tex_fl.width) % st->g.tex_fl.width;
	tex.y = (int)(floor.y * st->g.tex_fl.height) % st->g.tex_fl.height;
	draw_pixel(&st->g.main_scene, screen.x, screen.y,
		get_pixel_color(&st->g.tex_fl, tex.x, tex.y));
	draw_pixel(&st->g.main_scene, screen.x, MAIN_HEIGHT - screen.y - 1,
		get_pixel_color(&st->g.tex_cl, tex.x, tex.y));
}

static inline void	calculate_ray_direction(t_vector *ray_dir,
        t_app_state *st, t_point screen, double *denom)
{
	ray_dir->x = st->player.direction.x + st->player.plane.x
		* st->normal_x[screen.x];
	ray_dir->y = st->player.direction.y + st->player.plane.y
		* st->normal_x[screen.x];
	*denom = ray_dir->x * st->player.direction.x + ray_dir->y
		* st->player.direction.y;
}

void	render_ceiling_and_floor(t_app_state *st, int start_x, int end_x)
{
	int			idy;
	double		denom;
	t_vector	ray_dir;
	t_point		screen;

	screen.y = MAIN_HEIGHT / 2 + 1;
	idy = 0;
	while (screen.y < MAIN_HEIGHT)
	{
		screen.x = start_x;
		while (screen.x < end_x)
		{
			calculate_ray_direction(&ray_dir, st, screen, &denom);
			if (denom == 0)
			{
				screen.x++;
				continue ;
			}
			paint_pixels(st, screen, ray_dir, idy);
			screen.x++;
		}
		screen.y++;
		idy++;
	}
}
