/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:02 by joaomigu          #+#    #+#             */
/*   Updated: 2025/06/24 09:46:22 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Validates the file argument to ensure it is not empty 
 * and has the correct extension.
 *
 * @param arg The file argument to validate.
 * @return true if the file argument is valid, false otherwise.
 */
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

/**
 * @brief Checks the contents of the configuration file for validity 
 and processes the map section.
 *
 * This function parses the configuration fields, validates the map,
	and normalizes it for further use.
 *
 * @param cfg The configuration structure to update.
 * @param file_contents The array of strings containing the file contents.
 * @param line_count The total number of lines in the file.
 * @return true if the file contents are valid, false otherwise.
 */
static bool	check_file_contents(t_config *cfg, char **fc, size_t lc)
{
	size_t	index;
	size_t	msi;

	index = 0;
	if (!parse_configurations(cfg, fc, lc, &index))
		return (false);
	while (fc[index] && is_whitespace_line(fc[index]) && index < lc)
		index++;
	msi = index;
	if (!calculate_map_dimensions(cfg, fc, &index, lc))
		return (false);
	index = msi + cfg->map.range.y;
	while (fc[index] && index < lc)
	{
		if (!is_whitespace_line(fc[index]))
		{
			if (is_map_line(fc[index]))
				return (ft_putstr_fd(ERR_MAP_LINE, 2), false);
			else
				return (ft_putstr_fd(ERR_LAST_ELE, 2), false);
		}
		index++;
	}
	return (normalize_map(cfg, fc, msi, msi + cfg->map.range.y));
}

/**
 * @brief Validates the configuration and initializes the application state.
 *
 * This function validates the map, initializes fields,
	and sets up the player's position and direction.
 *
 * @param cfg The configuration structure containing the field data.
 * @param state The application state to initialize.
 * @return true if the configurations are valid and the state is initialized,
	false otherwise.
 */
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
	state->player.position.x = state->map->player_position.x + 0.5;
	state->player.position.y = state->map->player_position.y + 0.5;
	x = state->map->player_direction.x;
	y = state->map->player_direction.y;
	state->player.direction.x = x;
	state->player.direction.y = y;
	state->player.plane.x = -y * fov_factor;
	state->player.plane.y = x * fov_factor;
	return (true);
}

/**
 * @brief Loads the configuration file, validates its contents,
	and updates the configuration structure.
 *
 * This function reads the configuration file,
	validates its format and contents, and processes the map section.
 *
 * @param cfg The configuration structure to update.
 * @return true if the configurations were successfully loaded, false otherwise.
 */
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
