/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:10 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 15:51:55 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**

 * @brief Parses the configuration fields from the file contents and 
 updates the configuration structure.
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
static bool	isvalid_border(t_config *cfg, int i, int j)
{
	char	cur;

	cur = cfg->map.map[i][j];
	if (cur == '1')
		return (true);
	else if (cur != ' ')
	{
		if (i - 1 < 0 || j - 1 < 0)
			return (false);
		if (i - 1 >= 0 && (cfg->map.map[i - 1][j] == ' ' || cfg->map.map[i
				- 1][j] == '\0'))
			return (false);
		if (cfg->map.map[i + 1][j] == ' ' || cfg->map.map[i + 1][j] == '\0')
			return (false);
		if (j - 1 >= 0 && (cfg->map.map[i][j - 1] == ' ' || cfg->map.map[i][j
			- 1] == '\0'))
			return (false);
		if (cfg->map.map[i][j + 1] == ' ' || cfg->map.map[i][j + 1] == '\0')
			return (false);
	}
	return (true);
}

/**
 * @brief Sets the player's position and direction based on the map data.
 *
 * This function identifies the player's starting position and direction
 * (N, S, E, W) on the map and updates the configuration structure accordingly.
 *
 * @param i The row index of the player's position.
 * @param j The column index of the player's position.
 * @param cfg The configuration structure to update.
 */
static void	set_player(int i, int j, t_config *cfg)
{
	cfg->map.player_position.y = i;
	cfg->map.player_position.x = j;
	if (cfg->map.map[i][j] == 'N')
	{
		cfg->map.player_direction.x = 0;
		cfg->map.player_direction.y = -1;
	}
	if (cfg->map.map[i][j] == 'S')
	{
		cfg->map.player_direction.x = 0;
		cfg->map.player_direction.y = 1;
	}
	if (cfg->map.map[i][j] == 'W')
	{
		cfg->map.player_direction.x = -1;
		cfg->map.player_direction.y = 0;
	}
	if (cfg->map.map[i][j] == 'E')
	{
		cfg->map.player_direction.x = 1;
		cfg->map.player_direction.y = 0;
	}
}

/**
 * @brief Validates the map for correctness, including borders and player setup.
 *
 * This function checks the map for valid borders, ensures there is exactly one
 * player starting position, and validates the map's overall structure.
 *
 * @param cfg The configuration structure containing the map data.
 * @return true if the map is valid, false otherwise.
 */
bool	validate_map(t_config *cfg)
{
	int		i[2];
	char	c;

	i[0] = -1;
	while (cfg->map.map[++i[0]])
	{
		i[1] = -1;
		while (cfg->map.map[i[0]][++i[1]])
		{
			c = cfg->map.map[i[0]][i[1]];
			if (!isvalid_border(cfg, i[0], i[1]))
				return (ft_putstr_fd(ERR_BORDER, 2), false);
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				if (cfg->map.player_position.x != -1
					&& cfg->map.player_position.y != -1)
					return (ft_putstr_fd(ERR_DUP_PLAYER, 2), false);
				else
					set_player(i[0], i[1], cfg);
			}
		}
	}
	if (cfg->map.player_position.x < 0 || cfg->map.player_position.y < 0)
		return (ft_putstr_fd(ERR_NO_PLAYER, 2), false);
	return (true);
}

/**
 * @brief Checks if a string contains only allowed characters.
 *
 * This function iterates through the given string and verifies that each
 * character is part of the allowed `MAP_CHARS`. If an invalid character is
 * found, it returns false.
 *
 * @param str The string to check.
 * @return true if all characters are allowed, false otherwise.
 */
bool	is_valid_map_line(const char *str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        if (!is_allowed(str[i], MAP_CHARS))
            return (false);
        i++;
    }
    return (true);
}

/**
 * @brief Calculates the dimensions of the map based on the file contents.
 *
 * This function determines the width and height of the map by analyzing the
 * file contents and updates the configuration structure with the map's range.
 *
 * @param cfg The configuration structure to update.
 * @param file_contents The array of strings containing the file contents.
 * @param index Pointer to the current line index in the file.
 * @param line_count The total number of lines in the file.
 * @return true if the map dimensions were successfully calculated,
	false otherwise.
 */
bool	calculate_map_dimensions(t_config *cfg, char **file_contents,
		size_t *index, size_t line_count)
{
	size_t	line_length;
	int		i;

	line_length = 0;
	while (*index < line_count && file_contents[*index])
	{
		if (!is_whitespace_line(file_contents[*index]))
        {
			i = -1;
			while (file_contents[*index][++i])
			{
				if (file_contents[*index][i] == ' ')
					continue ;
				if (!is_allowed(file_contents[*index][i], MAP_CHARS))
					return (ft_putstr_fd(ERR_MAP_CHAR, 2), false);
			}
			line_length = ft_strlen(file_contents[*index]);
			if (line_length > (size_t)cfg->map.range.x)
				cfg->map.range.x = line_length;
			cfg->map.range.y++;
        }
		(*index)++;
	}
	return (true);
}

/**

 * @brief Normalizes the map by padding rows with spaces to ensure uniform width.
 *
 * This function allocates memory for the map, copies the file contents into
 * the map, and pads shorter rows with spaces to match the map's maximum width.
 *
 * @param cfg The configuration structure to update.
 * @param file_contents The array of strings containing the file contents.
 * @param map_start_index The starting index of the map in the file contents.
 * @param map_end_index The ending index of the map in the file contents.
 * @return true if the map was successfully normalized, false otherwise.
 */
bool	normalize_map(t_config *cfg, char **file_contents,
		size_t map_start_index, size_t map_end_index)
{
	size_t	i;
	size_t	index;

	index = 0;
	cfg->map.map = (char **)ft_calloc(cfg->map.range.y + 1, sizeof(char *));
	if (!cfg->map.map)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	while (map_start_index < map_end_index)
	{
		cfg->map.map[index] = (char *)ft_calloc(cfg->map.range.x + 1,
				sizeof(char));
		if (!cfg->map.map[index])
			return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
		i = 0;
		while (file_contents[map_start_index][i])
		{
			cfg->map.map[index][i] = file_contents[map_start_index][i];
			i++;
		}
		while (i < (size_t)cfg->map.range.x)
			cfg->map.map[index][i++] = ' ';
		map_start_index++;
		index++;
	}
	return (true);
}
