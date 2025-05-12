#include "../../inc/cub3d.h"

void	extract_rgb(const char *line, t_rgb *ref)
{
	char	**split;
	int		color_teste;

	while (*line && is_whitespace(*line))
		line++;
	split = ft_split(line, ',');
	if (!split || ft_str_array_len(split) != 3)
		return ;
	color_teste = ft_atoi(split[0]);
	if (color_teste >= 0 && color_teste <= 255)
		ref->red = color_teste;
	color_teste = ft_atoi(split[1]);
	if (color_teste >= 0 && color_teste <= 255)
		ref->green = color_teste;
	color_teste = ft_atoi(split[2]);
	if (color_teste >= 0 && color_teste <= 255)
		ref->blue = color_teste;
}

bool	validate_fields(t_config *cfg, t_app_state *state)
{
	if (!cfg || !state)
		return (false);
	return (true);
}

static bool	parse_config_item(char **target, char *id, char *str)
{
	if (*target)
	{
		ft_putstr_fd("Error.\nDuplicate ID found: ", 2);
		ft_putstr_fd(id, 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	*target = strtrim_dup(str);
	return (true);
}
static bool	parse_configuration_line(t_config *cfg, const char *line)
{
	if (*line && is_whitespace_line(line))
		return (true);
	while (*line && is_whitespace(*line))
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_config_item(&cfg->no_tex, "NO", (char *)line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_config_item(&cfg->so_tex, "SO", (char *)line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_config_item(&cfg->we_tex, "WE", (char *)line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_config_item(&cfg->ea_tex, "EA", (char *)line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_config_item(&cfg->fl_tex, "F", (char *)line + 2));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_config_item(&cfg->cl_tex, "C", (char *)line + 2));
	return (false);
}

bool	parse_configurations(t_config *cfg, char **file_contents,
		size_t line_count, size_t *index)
{
	while (file_contents[*index] && *index < line_count)
	{
		if (cfg->no_tex && cfg->so_tex && cfg->we_tex && cfg->ea_tex
			&& cfg->cl_tex && cfg->fl_tex)
			break ;
		if (!parse_configuration_line(cfg, file_contents[*index]))
		{
			ft_putstr_fd("Error.\nLine error on: '", 2);
			ft_putstr_fd(file_contents[*index], 2);
			return (ft_putstr_fd("'\n", 2), false);
		}
		(*index)++;
	}
	if (!cfg->no_tex || !cfg->so_tex || !cfg->we_tex || !cfg->ea_tex
		|| !cfg->cl_tex || !cfg->fl_tex)
		return (ft_putstr_fd("Error.\nMissing configurations fields\n", 2),
			false);
	return (true);
}
