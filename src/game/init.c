/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/13 18:41:32 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static inline int	game_loop(t_app_state *state)
{
	
	struct timeval va;
	struct timeval vb;
	int				frame_time; 
    int				fps;       

	gettimeofday(&va, NULL);
	
	mlx_clear_window(state->mlx, state->win);
	update_player(state);
	render_main_scene(state);
	mlx_put_image_to_window(state->mlx, state->win,
		state->g.main_scene.img_ptr, 0, 0);
	gettimeofday(&vb, NULL);
	if (va.tv_sec != 0 || va.tv_usec != 0)
    {
        frame_time = (vb.tv_sec - va.tv_sec) * 1000000 +
                     (vb.tv_usec - va.tv_usec);
        if (frame_time > 0)
            fps = 1000000 / frame_time; // Convert microseconds to FPS
        else
            fps = 0; // Avoid division by zero
    }
    else
    {
        frame_time = 0; // First frame, no previous time
        fps = 0;        // FPS is unknown for the first frame
    }
	mlx_string_put(state->mlx, state->win, 10,10, 0x000000, ft_itoa(fps));
	return (0);
}

static bool	init_mlx_image(t_img *img, void *mlx, int width, int height)
{
	img->img_ptr = mlx_new_image(mlx, width, height);
	if (!img->img_ptr)
		return (ft_putstr_fd(ERR_IMG_INIT, 2), false);
	img->height = height;
	img->width = width;
	img->half_height = height / 2;
	img->half_width = width / 2;
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->data_addr)
		return (ft_putstr_fd(ERR_IMG_DA, 2), false);
	return (true);
}

void	init_window(t_app_state *state)
{
	state->win = mlx_new_window(state->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!state->win)
		return (ft_putstr_fd(ERR_WIN_INIT, 2), (void)0);
	if (!init_mlx_image(&state->g.main_scene, state->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT))
		return (ft_putstr_fd(ERR_IMG_INIT, 2), (void)0);
	prec_normal_x(&state->normal_x, MAIN_WIDTH);
	if (!state->normal_x)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), (void)0);
	mlx_hook(state->win, KeyPress, KeyPressMask, handle_keypress,
		state);
	mlx_hook(state->win, KeyRelease, KeyReleaseMask, handle_keyrelease,
		state);
	mlx_hook(state->win, DestroyNotify, StructureNotifyMask, close_handler,
		state);
	mlx_loop_hook(state->mlx, game_loop, state);
	mlx_loop(state->mlx);
}




