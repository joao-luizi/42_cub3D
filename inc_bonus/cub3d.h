/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:20 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/24 14:20:47 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"


void				empty_letter(int src[5][3]);
void				get_character_pattern(char c, int letter[5][3]);
void				get_pattern_a(int src[5][3]);
void				get_pattern_b(int src[5][3]);
void				get_pattern_c(int src[5][3]);
void				get_pattern_d(int src[5][3]);
void				get_pattern_e(int src[5][3]);
void				get_pattern_f(int src[5][3]);
void				get_pattern_g(int src[5][3]);
void				get_pattern_h(int src[5][3]);
void				get_pattern_i(int src[5][3]);
void				get_pattern_j(int src[5][3]);
void				get_pattern_k(int src[5][3]);
void				get_pattern_l(int src[5][3]);
void				get_pattern_m(int src[5][3]);
void				get_pattern_n(int src[5][3]);
void				get_pattern_o(int src[5][3]);
void				get_pattern_p(int src[5][3]);
void				get_pattern_q(int src[5][3]);
void				get_pattern_k(int src[5][3]);
void				get_pattern_r(int src[5][3]);
void				get_pattern_s(int src[5][3]);
void				get_pattern_t(int src[5][3]);
void				get_pattern_u(int src[5][3]);
void				get_pattern_v(int src[5][3]);
void				get_pattern_w(int src[5][3]);
void				get_pattern_x(int src[5][3]);
void				get_pattern_y(int src[5][3]);
void				get_pattern_z(int src[5][3]);
void				get_pattern_zero(int src[5][3]);
void				get_pattern_one(int src[5][3]);
void				get_pattern_two(int src[5][3]);
void				get_pattern_three(int src[5][3]);
void				get_pattern_four(int src[5][3]);
void				get_pattern_five(int src[5][3]);
void				get_pattern_six(int src[5][3]);
void				get_pattern_seven(int src[5][3]);
void				get_pattern_eight(int src[5][3]);
void				get_pattern_nine(int src[5][3]);
void				get_pattern_hash(int src[5][3]);
void				get_pattern_plus(int src[5][3]);
void				get_pattern_minus(int src[5][3]);
void				get_pattern_dot(int src[5][3]);

// write_string.c
void				lib_x_write_string(char *str, int x, int y, t_img *section);

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
int	mouse_move_handler(int x, int y, t_app_state *st);
//		init
void		init_game(t_app_state *state);
//		minimap	
bool	init_fov_points(t_player *player);
bool	init_player_points(t_player *player);


//	render
//		main_scene
void		render_main_scene(t_app_state *st);
void		*raycast_routine(void *arg);
//		post_process
void	post_process(t_app_state *st, t_args *args);
void	print_fps(t_app_state *st);
//		render_horizontal
void		render_ceiling_and_floor(t_app_state *st, int start_x, int end_x);

//		render_perf
void		prec_normal(t_app_state *st);
//		render_utils
t_anim_slot	*find_door_anim(t_app_state *st, int x, int y);
int	get_obs_color(t_obstacle *obs, int screen_y, int obs_start, float blending_factor);
void		draw_pixel(t_img *img, int x, int y, int color);
bool		is_wall(double x, double y, t_app_state *st);
// 			render_vertical
void		initialize_ray(t_app_state *st, t_ray_info *r_info, int x);
void		setup_initial_step(t_app_state *st, t_ray_info *r_info);
void		dda(t_app_state *st, t_ray_info *r_info);
void		draw_column(t_app_state *st, t_ray_info *r_info, int x);
//	minimap
bool		is_player(t_app_state *st, int x, int y);
void		render_minimap(t_app_state *st, t_args *args);
//	minimap wall
bool		is_local_wall(t_app_state *st, int x, int y);
int			get_local_color(int x);
int			get_local_wall_color(t_app_state *st, int x, int y);
//	minimap color
int			get_color(t_app_state *st, int x, int y);
//		tex_utils
void	get_obs_tex(t_app_state *st, t_ray_info *r_info, t_obstacle *obs,
	int side);
int	get_pixel_color(t_img *img, int tex_x, int tex_y, float blending_factor);



//	setup
//		aux
size_t		count_file_lines(char *path);
bool		get_file_content(char *path, size_t line_count,
				char ***file_content);
bool		is_map_line(const char *line);
bool		is_allowed(char c, char *allowed);
bool		fill_texture(void *mlx, t_img *tex, char *file);
//		setup_animation
bool	load_animation(t_app_state *st, char **split, t_anim *anim);
bool	load_animation_frames(t_app_state *st, t_anim **anim, char *anim_file);
//		setup_map_utils
bool		validate_map(t_config *cfg);
//		setup_map
bool	isvalid_border(t_config *cfg, int i, int j);
void	set_player(int i, int j, t_config *cfg);
bool		calculate_map_dimensions(t_config *cfg, char **file_contents,
				size_t *index, size_t line_count);
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