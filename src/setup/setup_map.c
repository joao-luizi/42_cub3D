#include "../../inc/cub3d.h"

static bool	isvalid_border(t_config *cfg, int i, int j)
{
	char	cur;

	cur = cfg->map.map[i][j];
	if (cur == '1')
		return (true);
	else if (cur != ' ' )
	{
		if (i - 1 < 0 || j - 1 < 0)
			return (false);
		if (i - 1 >= 0 && (cfg->map.map[i - 1][j] == ' ' || cfg->map.map[i
				- 1][j] == '\0'))
			return (false);
		if (cfg->map.map[i + 1][j] == ' ' || cfg->map.map[i
			+ 1][j] == '\0')
			return (false);
		if (j - 1 >= 0 && (cfg->map.map[i][j - 1] == ' '
			|| cfg->map.map[i][j - 1] == '\0'))
			return (false);
		if (cfg->map.map[i][j + 1] == ' ' || cfg->map.map[i][j
			+ 1] == '\0')
			return (false);
	}
	return (true);
}

static void set_player(int i, int j, t_config *cfg)
{
	cfg->map.player_position.y = i;
	cfg->map.player_position.y = j;
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


bool validate_map(t_config *cfg)
{
	int i;
	int j;
	char c;
	i = 0;
	while (cfg->map.map[i])
	{
		j = 0;
		c = cfg->map.map[i][j];
		while (c)
		{
			if (!isvalid_border(cfg, i, j))
				return (ft_putstr_fd("Error.\nInvalid border detected.\n", 2), false);
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				if (cfg->map.player_position.x != -1 && cfg->map.player_position.y != -1)
					return (ft_putstr_fd("Error.\nDuplicate player position found.\n", 2), false);
				else
					set_player(i, j, cfg);
			}
			j++;
		}
		i++;
	}
}

bool	calculate_map_dimensions(t_config *cfg, char **file_contents,
		size_t *index, size_t line_count)
{
	size_t	line_length;

    line_length = 0;
	while (file_contents[*index] && is_map_line(file_contents[*index],
			MAP_CHARS) && *index < line_count)
	{
		line_length = ft_strlen(file_contents[*index]);
		if (line_length > (size_t)cfg->map.range.x)
			cfg->map.range.x = line_length;
		cfg->map.range.y++;
		(*index)++;
	}
	return (cfg->map.range.y > 2);
}

bool	normalize_map(t_config *cfg, char **file_contents,
		size_t map_start_index, size_t map_end_index)
{
	size_t	i;
	size_t	index;

	index = 0;
	cfg->map.map = (char **)ft_calloc(cfg->map.range.y + 1, sizeof(char *));
	if (!cfg->map.map)
		return (false);
	while (map_start_index < map_end_index)
	{
		cfg->map.map[index] = (char *)ft_calloc(cfg->map.range.x + 1,
				sizeof(char));
		if (!cfg->map.map[index])
			return (false);
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
