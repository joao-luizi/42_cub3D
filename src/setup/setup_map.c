#include "../../inc/cub3d.h"

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
