#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"

//	setup
//		init
void	init_config(t_config *cfg);
void	init_state(t_app_state *state);
//		cleanup
void	free_config(t_config *cfg, bool free_map);
void	free_array(char **arr);
void	free_state(t_app_state *state);
//		aux
size_t	count_file_lines(char *path);
bool	get_file_content(char *path, size_t line_count, char ***file_content);
bool	is_map_line(const char *line, char *allowed);
bool	fill_texture(void *mlx, t_img *tex, char *file);
bool	extract_rgb(const char *line, t_rgb *ref);
//		setup_map
bool	calculate_map_dimensions(t_config *cfg, char **file_contents,
			size_t *index, size_t line_count);
bool	validate_map(t_config *cfg);
bool	normalize_map(t_config *cfg, char **file_contents,
			size_t map_start_index, size_t map_end_index);

//		setup_fields
bool	parse_configurations(t_config *cfg, char **file_contents,
			size_t line_count, size_t *index);
bool 	validate_fields(t_config *cfg, t_app_state *state);
//		setup
bool	load_configurations(t_config *cfg);
bool	check_configurations(t_config *cfg, t_app_state *state);

// main
char	*strtrim_dup(char *ori);
bool	is_whitespace(char str);
bool	is_whitespace_line(const char *line);
size_t	ft_str_array_len(char **str);
#endif