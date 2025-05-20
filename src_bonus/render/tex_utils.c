#include "../../inc_bonus/cub3d.h"

int	get_pixel_color(t_img *img, int tex_x, int tex_y, float blending_factor)
{
    int		pixel;
    t_rgb	color;

    // Clamp blending factor to ensure it stays within valid range
    if (blending_factor >= MAX_BLEND_FACTOR)
        return (0x000000); // Fully black for maximum blending
    if (blending_factor < 0.0f)
        blending_factor = 0.0f;

    // Get the original pixel color
    pixel = *(int *)(img->data_addr + (tex_y * img->size_line + tex_x
                * (img->bpp / 8)));

    // If no blending is required, return the original color
    if (blending_factor == 0.0f)
        return (pixel);

    // Extract RGB components from the pixel
    color.red = (pixel >> 16) & 0xFF;
    color.green = (pixel >> 8) & 0xFF;
    color.blue = pixel & 0xFF;

    // Apply blending with black
    color.red = (int)(color.red * (1.0f - blending_factor));
    color.green = (int)(color.green * (1.0f - blending_factor));
    color.blue = (int)(color.blue * (1.0f - blending_factor));

    // Recombine the modified RGB components into a single color
    return ((color.red << 16) | (color.green << 8) | color.blue);
}
/* int	get_pixel_color(t_img *img, int tex_x, int tex_y, float blending_factor)
{
	int	pixel;
	t_rgb	color;
	
	
	if (blending_factor >= MAX_BLEND_FACTOR)
		return (0x000000);
	pixel = *(int *)(img->data_addr + (tex_y * img->size_line + tex_x
				* (img->bpp / 8)));
	if (blending_factor == 0)
		return (pixel);
	color.red = (pixel >> 16) & 0xFF;
	color.green = (pixel >> 8) & 0xFF;
	color.blue = pixel & 0xFF;
	color.red = (int)(color.red * (1.0f - blending_factor));
	color.green = (int)(color.green * (1.0f - blending_factor));
	color.blue = (int)(color.blue * (1.0f - blending_factor));
	return (pixel);
} */



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
