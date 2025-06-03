/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:06:10 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 14:06:34 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

static bool	validate_map_util(t_config *cfg, int i[2])
{
	char	c;

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
		if (c == 'D')
			cfg->map.door_count++;
	}
	return (true);
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

	i[0] = -1;
	while (cfg->map.map[++i[0]])
	{
		if (!validate_map_util(cfg, i))
			return (false);
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
