#include "../../inc/cub3d.h"
static void count_char(int *count, char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			(*count)++;
		i++;
	}
}
bool	extract_rgb(const char *line, int *ref)
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

bool	fill_texture(void *mlx, t_img *tex, char *file)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx, file, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		ft_putstr_fd(ERR_MISS_TEX, 2);
		ft_putstr_fd(file, 2);
		return (ft_putstr_fd("\n", 2), false);
	}
	tex->data_addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->size_line,
			&tex->endian);
	if (!tex->data_addr)
	{
		mlx_destroy_image(mlx, tex->img_ptr);
		tex->img_ptr = NULL;
		{
			ft_putstr_fd(ERR_MISS_TEX, 2);
			ft_putstr_fd(file, 2);
			return (ft_putstr_fd("\n", 2), false);
		}
	}
	return (true);
}

bool	get_file_content(char *path, size_t line_count, char ***file_content)
{
	char	*line;
	int		fd;
	int		i;

	*file_content = ft_calloc(sizeof(char *), line_count + 1);
	if (!(*file_content))
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_OPEN_FILE, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		return (ft_putstr_fd("\n", STDERR_FILENO), false);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line[ft_strlen(line) - 1] = '\0';
		// remove the ending newline (this is guarranteed to be there)
		(*file_content)[i] = line;
		i++;
	}
	close(fd);
	return (true);
}

size_t	count_file_lines(char *path)
{
	size_t	i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_OPEN_FILE, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		return (ft_putstr_fd("\n", STDERR_FILENO), i);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		i++;
		free(line);
	}
	close(fd);
	if (i == 0)
		ft_putstr_fd(ERR_EMPTY_CFG, STDERR_FILENO);
	return (i);
}
bool	is_allowed(char c, char *allowed)
{
	int	i;

	i = -1;
	while (allowed[++i])
	{
		if (allowed[i] == c)
			return (true);
	}
	return (false);
}
bool	is_map_line(const char *line)
{
	int	j;
	int	allowed_count;
	int	not_allowed_count;

	j = -1;
	allowed_count = 0;
	not_allowed_count = 0;
	while (line[++j])
	{
		if (line[j] == ' ')
			continue ;
		if (is_allowed(line[j], MAP_CHARS))
			allowed_count++;
		else
			not_allowed_count++;
	}
	if (allowed_count > 0 && not_allowed_count == 0)
		return (true);
	else
		return (false);
}
