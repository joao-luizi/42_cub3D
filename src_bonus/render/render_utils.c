/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 15:36:51 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

t_anim_slot	*find_door_anim(t_app_state *st, int x, int y)
{
	int i = 1; // anims[0] is reserved for face animation
	while (i < st->map->door_count + 1)
	{
		if (st->anims[i].map_point.x == x && st->anims[i].map_point.y == y)
			return (&st->anims[i]);
		i++;
	}
	return (NULL);
}

/**
 * @brief Retrieves the color of a specific pixel from a texture based on
 * ray information.
 *
 * @param img The texture image.
 * @param r_info The ray information structure containing wall details.
 * @param screen_y The y-coordinate on the screen.
 * @param wall_start The starting y-coordinate of the wall on the screen.
 * @return The color of the pixel in the texture.
 */

int	get_obs_color(t_obstacle *obs, int screen_y, int obs_start, float blending_factor)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	wall_pixel_offset;

	if (!obs->current_tex || blending_factor >= MAX_BLEND_FACTOR)
		return (0x000000);
	wall_pixel_offset = screen_y - obs_start;
	if (obs->flip_texture)
		tex_x = (int)((1.0 - obs->info.x) * obs->current_tex->width);
	else
		tex_x = (int)(obs->info.x * obs->current_tex->width);
	tex_y = (int)((wall_pixel_offset * obs->current_tex->height) / obs->info.y);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= obs->current_tex->width)
		tex_x = obs->current_tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= obs->current_tex->height)
		tex_y = obs->current_tex->height - 1;
	color = get_pixel_color(obs->current_tex, tex_x, tex_y, blending_factor);
	return (color);
}

/**
 * @brief Draws a single pixel on an image at the specified coordinates.
 *
 * @param img The image to draw on.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data_addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

/**
 * @brief Checks if a given position in the map is a wall or out of bounds.
 *
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @param st The application state containing the map data.
 * @return true if the position is a wall or out of bounds, false
 * otherwise.
 */
bool	is_wall(double x, double y, t_app_state *st)
{
	int	map_x;
	int	map_y;
	t_anim_slot	*anim;
	
	map_x = (int)x;
	map_y = (int)y;
	if (map_x <= 0 || map_y <= 0 || map_x >= st->map->range.x
		|| map_y >= st->map->range.y)
		return (true);
	if (st->map->map[map_y][map_x] == ' ' || st->map->map[map_y][map_x] == '\0')
		return (true);
	if (st->map->map[map_y][map_x] == '1')
		return (true);
	if (st->map->map[map_y][map_x] == 'D')
	{
		anim = find_door_anim(st, map_x, map_y);
		if (anim && anim->is_started)
			return (false);
		else
			return (true);
	}
	return (false);
}
