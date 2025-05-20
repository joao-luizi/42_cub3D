/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:20 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 15:37:01 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"

//	common
//		aux.
char		*strtrim_dup(char *ori);
bool		is_whitespace(char str);
bool		is_whitespace_line(const char *line);
size_t		ft_str_array_len(char **str);
void		count_char(int *count, char c, char *str);
//		cleanup_g
void		free_graphics(t_graphics *g, void *mlx);
//		cleanup
void		free_array(char **arr);
void		free_config(t_config *cfg, bool free_map);
void		free_state(t_app_state *state);
void		free_obstacles(t_obstacle *head);
//		init
void		init_config(t_config *cfg);
void		init_state(t_app_state *state);

//	game
//		aux
bool		init_animations(t_app_state *state);
bool		init_threads_and_buffers(t_app_state *state);
//		game_loop
int			game_loop(t_app_state *st);
//		game
void		update_player(t_app_state *state);
//		hooks
int			handle_keypress(int keycode, t_app_state *state);
int			handle_keyrelease(int keycode, t_app_state *state);
int			close_handler(t_app_state *state);
//		init
void		init_game(t_app_state *state);

//	render
//		main_scene
void		render_main_scene(t_app_state *st, struct timeval *now);
void		*raycast_routine(void *arg);
//		post_process
void		post_process(t_app_state *st, struct timeval *now);
//		render_horizontal
void		render_ceiling_and_floor(t_app_state *st, int start_x, int end_x);

//		render_perf
void		prec_normal(t_app_state *st);
//		render_utils
t_anim_slot	*find_door_anim(t_app_state *st, int x, int y);
int			get_obs_color(t_obstacle *obs, int screen_y, int obs_start);
void		draw_pixel(t_img *img, int x, int y, int color);
bool		is_wall(double x, double y, t_app_state *st);
// 			render_vertical
void		initialize_ray(t_app_state *st, t_ray_info *r_info, int x);
void		setup_initial_step(t_app_state *st, t_ray_info *r_info);
void		dda(t_app_state *st, t_ray_info *r_info);
void		draw_column(t_app_state *st, t_ray_info *r_info, int x);
//		tex_utils
void	get_obs_tex(t_app_state *st, t_ray_info *r_info, t_obstacle *obs,
	int side);
//	setup
//		aux
size_t		count_file_lines(char *path);
bool		get_file_content(char *path, size_t line_count,
				char ***file_content);
bool		is_map_line(const char *line);
bool		is_allowed(char c, char *allowed);
bool		fill_texture(void *mlx, t_img *tex, char *file);
//		setup_map
bool		calculate_map_dimensions(t_config *cfg, char **file_contents,
				size_t *index, size_t line_count);
bool		validate_map(t_config *cfg);
bool		normalize_map(t_config *cfg, char **file_contents,
				size_t map_start_index, size_t map_end_index);
//		setup_fields
bool		parse_configurations(t_config *cfg, char **file_contents,
				size_t line_count, size_t *index);
bool		validate_fields(t_config *cfg, t_app_state *state);
//		setup
bool		load_configurations(t_config *cfg);
bool		check_configurations(t_config *cfg, t_app_state *state);

// main

#endif