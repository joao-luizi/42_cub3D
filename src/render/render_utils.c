/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/13 15:33:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_tex_color(t_img *img, t_ray_info *r_info, int screen_y, int wall_start)
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
