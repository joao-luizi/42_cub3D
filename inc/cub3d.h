/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:20 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 18:16:40 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"

//	common
//		aux.
char	*strtrim_dup(char *ori);
bool	is_whitespace(char str);
bool	is_whitespace_line(const char *line);
size_t	ft_str_array_len(char **str);
void	count_char(int *count, char c, char *str);
//		cleanup
void	free_config(t_config *cfg, bool free_map);
void	free_array(char **arr);
void	free_state(t_app_state *state);
//		init
void	init_config(t_config *cfg);
void	init_state(t_app_state *state);

//	game
//		game
void	update_player(t_app_state *state);
//		hooks
int		handle_keypress(int keycode, t_app_state *state);
int		handle_keyrelease(int keycode, t_app_state *state);
int		close_handler(t_app_state *state);
//		init
void	init_window(t_app_state *state);

//	render
//		render_utils
bool	is_wall(double x, double y, t_app_state *st);
void	draw_pixel(t_img *img, int x, int y, int color);
void	get_wall_tex(t_img **wall_tex, t_wall wall, t_app_state *st);
void	precompute_column(t_app_state *st, int wall[2], t_ray_info *r_info,
			t_img *wall_tex);
//		render_perf
void	prec_normal_x(double **normal_x, int width);
//		main_scene
void	render_main_scene(t_app_state *st);
//	setup
//		aux
size_t	count_file_lines(char *path);
bool	get_file_content(char *path, size_t line_count, char ***file_content);
bool	is_map_line(const char *line);
bool	is_allowed(char c, char *allowed);
bool	fill_texture(void *mlx, t_img *tex, char *file);
//		setup_map
bool	calculate_map_dimensions(t_config *cfg, char **file_contents,
			size_t *index, size_t line_count);
bool	validate_map(t_config *cfg);
bool	normalize_map(t_config *cfg, char **file_contents,
			size_t map_start_index, size_t map_end_index);
//		setup_fields
bool	parse_configurations(t_config *cfg, char **file_contents,
			size_t line_count, size_t *index);
bool	validate_fields(t_config *cfg, t_app_state *state);
//		setup
bool	load_configurations(t_config *cfg);
bool	check_configurations(t_config *cfg, t_app_state *state);

// main

#endif