#include "../../inc/cub3d.h"

static bool	validate_file_argument(char *arg)
{
	int	arg_len;

	if (!arg)
		return (ft_putstr_fd(ERR_EMPTY_ARG, 2), false);
	arg_len = ft_strlen(arg);
	if (arg_len < 4 || ft_strncmp(arg + arg_len - 4, ".cub", 4))
		return (ft_putstr_fd(ERR_FILE_EXT, 2), false);
	return (true);
}

static bool	check_file_contents(t_config *cfg, char **file_contents,
		size_t line_count)
{
	size_t	index;
	size_t	map_start_index;
	size_t	map_end_index;

	index = 0;
	if (!parse_configurations(cfg, file_contents, line_count, &index))
		return (false);
	while (file_contents[index] && is_whitespace_line(file_contents[index])
		&& index < line_count)
		index++;
	map_start_index = index;
	if (!calculate_map_dimensions(cfg, file_contents, &index, line_count))
		return (false);
	map_end_index = index;
	while (file_contents[index] && index < line_count)
	{
		if (!is_whitespace_line(file_contents[index]))
		{
			if (is_map_line(file_contents[index],MAP_CHARS))
				return (ft_putstr_fd(ERR_MAP_LINE, 2), false);
			else
				return (ft_putstr_fd(ERR_LAST_ELE, 2), false);
		}
		index++;
	}
	return (normalize_map(cfg, file_contents, map_start_index, map_end_index));
}

bool	check_configurations(t_config *cfg, t_app_state *state)
{
	double	fov_factor;
	double	x;
	double	y;

	if (!validate_map(cfg))
		return (false);
	if (!validate_fields(cfg, state))
		return (false);
	fov_factor = (double)FOV / 100;
	state->map = &cfg->map;
	x = state->map->player_position.x + 0.5;
	y = state->map->player_position.y + 0.5;
	state->player.plane.x = -y * fov_factor;
	state->player.plane.y = x * fov_factor;
	state->player.direction.x = state->map->player_direction.x;
	state->player.direction.y = state->map->player_direction.y;
	state->player.position.x = x;
	state->player.position.y = y;
	return (true);
}

bool	load_configurations(t_config *cfg)
{
	size_t	line_count;
	char	**file_content;

	file_content = NULL;
	if (!validate_file_argument(cfg->normal_file_path))
		return (free_array(file_content), false);
	line_count = count_file_lines(cfg->normal_file_path);
	if (line_count == 0)
		return (free_array(file_content), false);
	file_content = NULL;
	if (!get_file_content(cfg->normal_file_path, line_count, &file_content))
		return (free_array(file_content), false);
	if (!check_file_contents(cfg, file_content, line_count))
		return (free_array(file_content), false);
	return (free_array(file_content), true);
}
