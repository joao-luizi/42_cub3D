/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_horizontal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/19 16:04:18 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static int get_pixel_color(t_img *img, int tex_x, int tex_y)
{
    int pixel;

    pixel = *(int *)(img->data_addr + (tex_y * img->size_line + tex_x
            * (img->bpp / 8)));
    return (pixel);
}

void render_ceiling_and_floor(t_app_state *st, int start_x, int end_x)
{
    int y;
    int idy;
    int x;
    double weight;
    double ray_dir_x, ray_dir_y;
    double floor_x, floor_y;
    int tex_x, tex_y;
    
    //printf("Rendering ceiling and floor from %d to %d\n", start_x, end_x);
    y = MAIN_HEIGHT / 2 + 1;
    idy = 0;
    while (y < MAIN_HEIGHT)
    {
        x = start_x;
        while (x < end_x)
        {
            ray_dir_x = st->player.direction.x + st->player.plane.x * st->normal_x[x];
            ray_dir_y = st->player.direction.y + st->player.plane.y * st->normal_x[x];
            double denom = ray_dir_x * st->player.direction.x + ray_dir_y * st->player.direction.y;
            if (denom == 0)
            {
                x++;
                continue;
            }
            weight = st->normal_y[idy] / denom;
            
            // Calculate the real world coordinates of the floor/ceiling point
            floor_x = st->player.position.x + weight * ray_dir_x;
            floor_y = st->player.position.y + weight * ray_dir_y;
            
            // Map the world coordinates to texture coordinates
            tex_x = (int)(floor_x * st->g.tex_fl.width) % st->g.tex_fl.width;
            tex_y = (int)(floor_y * st->g.tex_fl.height) % st->g.tex_fl.height;
            // Fetch the pixel from the floor texture

            int floor_color = get_pixel_color(&st->g.tex_fl, tex_x, tex_y);
            // Draw the floor pixel
            draw_pixel(&st->g.main_scene, x, y, floor_color);
            // For the ceiling, invert the y-coordinate
            
            int ceiling_color = get_pixel_color(&st->g.tex_cl, tex_x, tex_y);
            // Fetch the pixel from the ceiling texture

            // Draw the ceiling pixel
            draw_pixel(&st->g.main_scene, x, MAIN_HEIGHT - y - 1, ceiling_color);
            x++;
        } 
        y++;
        idy++;
    }
}
