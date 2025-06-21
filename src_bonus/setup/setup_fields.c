/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/06/21 17:06:37 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Extracts RGB color values from a string and converts them into
 * a single integer.
 * @param line The string containing the RGB values separated by commas.
 * @param ref Pointer to the integer where the resulting color will be stored.
 * @return true if the RGB values were successfully extracted and valid,
	false otherwise.
 */
bool	extract_rgb(const char *line, int *ref)
{
	char	**split;
	int		color[4];

	color[3] = 0;
	while (*line && is_whitespace(*line))
		line++;
	count_char(&color[3], ',', (char *)line);
	if (color[3] != 2)
		return (ft_putstr_fd(ERR_COLOR_FORMAT, 2), ft_putstr_fd((char *)line,
				2), ft_putstr_fd("\n", 2), false);
	split = ft_split(line, ',');
	if (!split || ft_str_array_len(split) != 3 || is_whitespace_line(split[0])
		|| is_whitespace_line(split[1]) || is_whitespace_line(split[2]))
		return (free_array(split), ft_putstr_fd(ERR_COLOR_FORMAT, 2),
			ft_putstr_fd((char *)line, 2), ft_putstr_fd("\n", 2), false);
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (free_array(split), ft_putstr_fd(ERR_COLOR_FORMAT, 2),
			ft_putstr_fd((char *)line, 2), ft_putstr_fd("\n", 2), false);
	*ref = (color[0] << 16) | (color[1] << 8) | color[2];
	return (free_array(split), true);
}

/**

 * @brief Validates and initializes the fields in the configuration
 and application state.
 *
 * This function initializes MiniLibX, loads textures,
	and extracts RGB values for floor
 * and ceiling colors.
 *
 * @param cfg The configuration structure containing the field data.
 * @param state The application state to initialize.
 * @return true if all fields were successfully validated and initialized,
	false otherwise.
 */
bool	validate_fields(t_config *cfg, t_app_state *state)
{
	state->mlx = mlx_init();
	if (!state->mlx)
		return (ft_putstr_fd(ERR_MLX_INIT, 2), false);
	if (!fill_texture(state->mlx, &state->g.tex_no, cfg->no_tex)
		|| !fill_texture(state->mlx, &state->g.tex_so, cfg->so_tex)
		|| !fill_texture(state->mlx, &state->g.tex_we, cfg->we_tex)
		|| !fill_texture(state->mlx, &state->g.tex_ea, cfg->ea_tex)
		|| !fill_texture(state->mlx, &state->g.tex_fl, cfg->fl_tex)
		|| !fill_texture(state->mlx, &state->g.tex_cl, cfg->cl_tex))
		return (false);
	if (!load_animation_frames(state, &state->g.door_anim, cfg->door_anim))
		return (false);
	if (!load_animation_frames(state, &state->g.face_anim, cfg->face_anim))
		return (false);
	return (true);
}

/**
 * @brief Parses a configuration item and assigns its value to the
 * target field.
 *
 * @param target Pointer to the target field where the parsed value will
 * be stored.
 * @param id The identifier of the configuration item (e.g., "NO", "SO").
 * @param str The string containing the value of the configuration item.
 * @return true if the configuration item was successfully parsed,
	false otherwise.
 */
static bool	parse_item(char **target, char *id, char *str)
{
	if (*target)
	{
		ft_putstr_fd(ERR_DUP_ID, 2);
		ft_putstr_fd(id, 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	*target = strtrim_dup(str);
	return (true);
}

/**
 * @brief Parses a single line of the configuration file and updates
 * the configuration structure.
 *
 * @param cfg The configuration structure to update.
 * @param line The line from the configuration file to parse.
 * @return true if the line was successfully parsed, false otherwise.
 */
static bool	parse_configuration_line(t_config *cfg, const char *line)
{
	if (*line && is_whitespace_line(line))
		return (true);
	while (*line && is_whitespace(*line))
		line++;
	if (!*line)
		return (true);
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_item(&cfg->no_tex, "NO", (char *)line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_item(&cfg->so_tex, "SO", (char *)line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_item(&cfg->we_tex, "WE", (char *)line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_item(&cfg->ea_tex, "EA", (char *)line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_item(&cfg->fl_tex, "F", (char *)line + 2));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_item(&cfg->cl_tex, "C", (char *)line + 2));
	if (!ft_strncmp(line, "ANIM_DOOR ", 10))
		return (parse_item(&cfg->door_anim, "ANIM_DOOR", (char *)line + 10));
	if (!ft_strncmp(line, "ANIM_FACE ", 10))
		return (parse_item(&cfg->face_anim, "ANIM_FACE", (char *)line + 10));
	ft_putstr_fd("Error.\nUnrecognized field line: ", 2);
	return (ft_putstr_fd((char *)line, 2), ft_putstr_fd("\n", 2), false);
}

/**

 * @brief Parses the configuration fields from the file contents
 and updates the configuration structure.
 *
 * This function iterates through the file contents,
 parsing configuration fields until the map section
 * is reached.
 *
 * @param cfg The configuration structure to update.
 * @param file_contents The array of strings containing the file contents.
 * @param line_count The total number of lines in the file.
 * @param index Pointer to the current line index,
	which will be updated during parsing.
 * @return true if all configuration fields were successfully parsed,
	false otherwise.
 */
bool	parse_configurations(t_config *cfg, char **file_contents,
		size_t line_count, size_t *index)
{
	while (file_contents[*index] && *index < line_count
		&& !is_map_line(file_contents[*index]))
	{
		if (!parse_configuration_line(cfg, file_contents[*index]))
			return (false);
		(*index)++;
	}
	if (!cfg->no_tex || !cfg->so_tex || !cfg->we_tex || !cfg->ea_tex
		|| !cfg->cl_tex || !cfg->fl_tex || !cfg->door_anim || !cfg->face_anim)
		return (ft_putstr_fd(ERR_FIELDS, 2), false);
	return (true);
}
