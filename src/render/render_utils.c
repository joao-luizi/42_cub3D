/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 15:30:52 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static inline int	get_tex_color(t_img *img, t_ray_info *r_info, int screen_y, int wall_start)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	wall_pixel_offset;

	if (!img)
		return (0x000000);
	wall_pixel_offset = screen_y - wall_start;
	if (r_info->wall == SO_WALL || r_info->wall == WE_WALL)
		tex_x = (int)((1.0 - r_info->wall_info.x) * img->width);
	else
		tex_x = (int)(r_info->wall_info.x * img->width);
	tex_y = (int)((wall_pixel_offset * img->height) / r_info->wall_info.y);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= img->height)
		tex_y = img->height - 1;
	color = *(int *)(img->data_addr + (tex_y * img->size_line + tex_x
				* (img->bpp / 8)));
	return (color);
}

void	precompute_column(t_app_state *st, int wall[2],
		t_ray_info *r_info, t_img *wall_tex)
{
	int	k;
	int	tex_i;

	k = 0;
	if (k < wall[0])
		k = wall[0];
	tex_i = 0;
	while (k <= wall[1] && k < MAIN_HEIGHT)
	{
		if (wall_tex)
			st->column_buffer[tex_i] = get_tex_color(wall_tex, r_info, k,
					wall[0]);
		tex_i++;
		k++;
	}
}



void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data_addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

bool	is_wall(double x, double y, t_app_state *st)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x <= 0 || map_y <= 0 || map_x >= st->map->range.x
		|| map_y >= st->map->range.y)
		return (true);
	if (st->map->map[map_y][map_x] == ' ' || st->map->map[map_y][map_x] == '\0')
		return (true);
	return (false);
}

void	get_wall_tex(t_img **wall_tex, t_wall wall, t_app_state *st)
{
	if (wall == NO_WALL)
		*wall_tex = &st->g.tex_no;
	else if (wall == SO_WALL)
		*wall_tex = &st->g.tex_so;
	else if (wall == WE_WALL)
		*wall_tex = &st->g.tex_we;
	else if (wall == EA_WALL)
		*wall_tex = &st->g.tex_ea;
	else
		*wall_tex = NULL;
}