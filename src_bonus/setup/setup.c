#include "../../inc_bonus/cub3d.h"

static bool	validate_file_argument(char *arg)
{
	int	arg_len;

	if (!arg)
		return (ft_putstr_fd("Error.\nEmpty file argument.\n", STDERR_FILENO),
			false);
	arg_len = ft_strlen(arg);
	if (arg_len < 4 || ft_strncmp(arg + arg_len - 4, ".cub", 4))
		return (ft_putstr_fd("Error.\nWrong file extension. Expected '.cub'.\n",
				STDERR_FILENO), false);
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
		return (false);
	index++;
}
return (normalize_map(cfg, file_contents, map_start_index, map_end_index));
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
	printf("load_configuration: OK\n");
	return (free_array(file_content), true);
}
