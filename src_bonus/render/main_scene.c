/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:25:44 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/18 23:05:57 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static inline void after_wait(t_app_state *st)
{
    pthread_mutex_lock(&st->render_mutex);
    st->threads_done++;
    if (st->threads_done == st->core_count)
    {
        st->render_ready = false;
        pthread_cond_signal(&st->render_cond);
    }
    pthread_mutex_unlock(&st->render_mutex); 
}
static inline bool pre_wait(t_app_state *st)
{
    pthread_mutex_lock(&st->render_mutex);
    while (!st->render_ready && !st->exit_requested)
        pthread_cond_wait(&st->render_cond, &st->render_mutex);
    if (st->exit_requested)
    {
        pthread_mutex_unlock(&st->render_mutex);
        return (false);
    }
    pthread_mutex_unlock(&st->render_mutex); 
    return (true);
}

static inline void setup_initial_step(t_app_state *st, t_ray_info *r_info)
{
    if (r_info->ray_dir.x < 0)
    {
        r_info->step.x = -1;
        r_info->side_dist.x = (st->player.position.x - r_info->map.x)
            * r_info->delta_dist.x;
    }
    else
    {
        r_info->step.x = 1;
        r_info->side_dist.x = (r_info->map.x + 1.0 - st->player.position.x)
            * r_info->delta_dist.x;
    }
    if (r_info->ray_dir.y < 0)
    {
        r_info->step.y = -1;
        r_info->side_dist.y = (st->player.position.y - r_info->map.y)
            * r_info->delta_dist.y;
    }
    else
    {
        r_info->step.y = 1;
        r_info->side_dist.y = (r_info->map.y + 1.0 - st->player.position.y)
            * r_info->delta_dist.y;
    }
}
static inline void initialize_ray(t_app_state *st, t_ray_info *r_info, int x)
{
    double camera_x;

    // Calculate the x-coordinate in camera space
    r_info->ray_dir.x = st->player.direction.x + st->player.plane.x
			* st->normal_x[x];
    r_info->ray_dir.y = st->player.direction.y + st->player.plane.y
			* st->normal_x[x];

    // Initialize the map position (current square of the player)
    r_info->map.x = (int)st->player.position.x;
    r_info->map.y = (int)st->player.position.y;

    // Calculate delta distances
    r_info->delta_dist.x = fabs(1 / r_info->ray_dir.x);
    r_info->delta_dist.y = fabs(1 / r_info->ray_dir.y);

    // Initialize other fields to default values
    r_info->wall_dist = 0;
    r_info->wall_half = 0;
    r_info->wall_info.x = 0;
    r_info->wall_info.y = 0;
    r_info->wall_text = NULL;
    r_info->obstacles = NULL;
    r_info->wall = NONE_WALL
}

static void render_ceiling_and_floor(t_app_state *st, int x)
{
    int y;
    double row_distance;
    double floor_x, floor_y;
    double weight;
    int tex_x, tex_y;

    t_img *floor_texture = st->textures.floor;
    t_img *ceiling_texture = st->textures.ceiling;

    for (y = MAIN_HEIGHT / 2; y < MAIN_HEIGHT; y++) // Floor
    {
        // Calculate the distance from the player to the floor plane
        row_distance = (0.5 * MAIN_HEIGHT) / (y - MAIN_HEIGHT / 2);

        // Calculate the real-world coordinates of the floor point
        weight = row_distance / st->player.plane_dist;
        floor_x = st->player.position.x + weight * (st->player.dir.x + st->player.plane.x * (2 * x / (double)MAIN_WIDTH - 1));
        floor_y = st->player.position.y + weight * (st->player.dir.y + st->player.plane.y * (2 * x / (double)MAIN_WIDTH - 1));

        // Map the world coordinates to texture coordinates
        tex_x = (int)(floor_x * floor_texture->width) % floor_texture->width;
        tex_y = (int)(floor_y * floor_texture->height) % floor_texture->height;

        // Fetch the pixel from the floor texture
        int floor_color = get_texture_pixel(floor_texture, tex_x, tex_y);

        // Draw the floor pixel
        put_pixel_to_image(st->image, x, y, floor_color);

        // For the ceiling, invert the y-coordinate
        int ceiling_y = MAIN_HEIGHT - y - 1;

        // Fetch the pixel from the ceiling texture
        int ceiling_color = get_texture_pixel(ceiling_texture, tex_x, tex_y);

        // Draw the ceiling pixel
        put_pixel_to_image(st->image, x, ceiling_y, ceiling_color);
    }
}

void *raycast_routine(void *arg)
{
    t_args      *args;
    t_app_state *st;
    t_ray_info  r_info;
    int         x;

    args = (t_args *)arg;
    st = args->st;
    
    while (true)
    {
        if (!pre_wait(st))
            break;
            
        for (x = args->start_col; x < args->end_col; x++)
        {
            render_ceiling_and_floor(st, x);
        }
        x = args->start_col - 1;
        while (++x < args->end_col)
        {
            initialize_ray(st, &r_info, x);
            setup_initial_step(st, &r_info);
            // get_wall
            // draw_column
        }
        after_wait(st);
    }
    printf("Thread exiting...\n");
    return (NULL);
}
/**
 * @brief Renders the main scene by casting rays and drawing the
 * corresponding wall slices.
 *
 * @param st The application state containing the game's data.
 */
void render_main_scene(t_app_state *st)
{
    // Signal threads to start rendering
    pthread_mutex_lock(&st->render_mutex);
    st->render_ready = true;
    st->threads_done = 0;
    pthread_cond_broadcast(&st->render_cond);
    pthread_mutex_unlock(&st->render_mutex);

    // Wait for threads to finish or exit if requested
    pthread_mutex_lock(&st->render_mutex);
    while (st->threads_done < st->core_count && !st->exit_requested)
        pthread_cond_wait(&st->render_cond, &st->render_mutex);
    pthread_mutex_unlock(&st->render_mutex);

    // If exit_requested is true, handle cleanup or exit logic if needed
    if (st->exit_requested)
    {
        printf("Render main scene exiting early due to exit request.\n");
        return;
    }
}
