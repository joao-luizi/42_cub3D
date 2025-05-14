/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 18:14:33 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	extract_rgb(const char *line, int *ref)
{
	char	**split;
	int		color[4];

	color[3] = 0;
	while (*line && is_whitespace(*line))
		line++;
	count_char(&color[3], ' ', (char *)line);
	if (color[3] > 2)
		return (ft_putstr_fd(ERR_COLOR_FORMAT, 2), ft_putstr_fd((char *)line,
				2), ft_putstr_fd("\n", 2), false);
	split = ft_split(line, ',');
	if (!split)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
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

bool	validate_fields(t_config *cfg, t_app_state *state)
{
	state->mlx = mlx_init();
	if (!state->mlx)
		return (ft_putstr_fd(ERR_MLX_INIT, 2), false);
	if (!fill_texture(state->mlx, &state->g.tex_no, cfg->no_tex)
		|| !fill_texture(state->mlx, &state->g.tex_so, cfg->so_tex)
		|| !fill_texture(state->mlx, &state->g.tex_we, cfg->we_tex)
		|| !fill_texture(state->mlx, &state->g.tex_ea, cfg->ea_tex)
		|| !extract_rgb(cfg->fl_tex, &state->g.floor)
		|| !extract_rgb(cfg->cl_tex, &state->g.ceil))
		return (false);
	return (true);
}

static bool	parse_config_item(char **target, char *id, char *str)
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

static bool	parse_configuration_line(t_config *cfg, const char *line)
{
	if (*line && is_whitespace_line(line))
		return (true);
	while (*line && is_whitespace(*line))
		line++;
	if (!*line)
		return (true);
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
	ft_putstr_fd("Error.\nUnrecognized field line: ", 2);
	ft_putstr_fd((char *)line, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}

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
		|| !cfg->cl_tex || !cfg->fl_tex)
		return (ft_putstr_fd(ERR_FIELDS, 2), false);
	return (true);
}
