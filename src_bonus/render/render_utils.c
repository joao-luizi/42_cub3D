/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:26:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/17 23:00:57 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

t_anim_slot *find_door_anim(t_app_state *st, int x, int y)
{
    int i = 1; // anims[0] is reserved for face animation
    while (i < st->map->door_count + 1)
    {
        if (st->anims[i].map_point.x == x && st->anims[i].map_point.y == y)
            return &st->anims[i];
        i++;
    }
    return NULL;
}

static inline int	get_door_color(t_img *img, t_ray_info *r_info, int screen_y,
		int wall_start)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	wall_pixel_offset;

	if (!img)
		return (0x000000);
	wall_pixel_offset = screen_y - wall_start;
	//if (r_info->wall == SO_WALL || r_info->wall == WE_WALL)
	//	tex_x = (int)((1.0 - r_info->door_info.x) * img->width);
	//else
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

void	precompute_door(int *colbuffer, int wall[2], t_ray_info *r_info,
		t_img *wall_tex)
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
			colbuffer[tex_i] = get_door_color(wall_tex, r_info, k,
					wall[0]);
		tex_i++;
		k++;
	}
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
static inline int	get_tex_color(t_img *img, t_ray_info *r_info, int screen_y,
		int wall_start)
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

/**
 * @brief Precomputes the colors for a vertical column of pixels 
 * representing a wall slice.
 * 
 * @param st The application state containing the game's data.
 * @param wall An array containing the start and end y-coordinates of the 
 * wall slice.
 * @param r_info The ray information structure containing wall details.
 * @param wall_tex The texture image for the wall.
 */
void	precompute_column(int *colbuffer, int wall[2], t_ray_info *r_info,
		t_img *wall_tex)
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
			colbuffer[tex_i] = get_tex_color(wall_tex, r_info, k,
					wall[0]);
		tex_i++;
		k++;
	}
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

	map_x = (int)x;
	map_y = (int)y;
	if (map_x <= 0 || map_y <= 0 || map_x >= st->map->range.x
		|| map_y >= st->map->range.y)
		return (true);
	if (st->map->map[map_y][map_x] == ' ' || st->map->map[map_y][map_x] == '\0')
		return (true);
	if (st->map->map[map_y][map_x] == 'D' || st->map->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

/**
 * @brief Retrieves the appropriate wall texture based on the wall type.
 * 
 * @param wall_tex Pointer to the texture image to set.
 * @param wall The type of wall (e.g., NO_WALL, SO_WALL).
 * @param st The application state containing the texture data.
 */
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
