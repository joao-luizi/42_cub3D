/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 16:55:10 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static inline void print_fps(time_t previous_sec, time_t previous_usec, t_app_state *st)
{
	struct timeval current;
	int				frame_time; 
    int				fps;  
	char *			itoa;
	
	gettimeofday(&current, NULL);
	if (previous_sec != 0 || previous_usec != 0)
    {
        frame_time = (current.tv_sec - previous_sec) * 1000000 +
                     (current.tv_usec - previous_usec);
        if (frame_time > 0)
            fps = 1000000 / frame_time;
        else
            fps = 0; 
    }
    else
    {
        frame_time = 0;
        fps = 0;        
    }
	itoa = ft_itoa(fps);
	mlx_string_put(st->mlx, st->win, 10,10, 0x000000, "FPS:");
	mlx_string_put(st->mlx, st->win, 50,10, 0x000000, itoa);
	free(itoa);
}
static inline int	game_loop(t_app_state *st)
{
	
	struct timeval va;
	 

	gettimeofday(&va, NULL);
	
	mlx_clear_window(st->mlx, st->win);
	update_player(st);
	render_main_scene(st);
	mlx_put_image_to_window(st->mlx, st->win,
		st->g.main_scene.img_ptr, 0, 0);
	if (st->g.fps)
		print_fps(va.tv_sec, va.tv_usec, st);
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
	state->column_buffer = ft_calloc(MAIN_HEIGHT, sizeof(int));
	if (!state->column_buffer)
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




