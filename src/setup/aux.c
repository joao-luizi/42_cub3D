#include "../../inc/cub3d.h"

bool	extract_rgb(const char *line, t_rgb *ref)
{
	char	**split;
	int		color_teste;

	while (*line && is_whitespace(*line))
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	if (ft_str_array_len(split) != 3)
	{
		ft_putstr_fd(ERR_COLOR_FORMAT, 2);
		ft_putstr_fd((char *)line, 2);
		return (ft_putstr_fd("\n", 2), false);
	}
	color_teste = ft_atoi(split[0]);
	if (color_teste >= 0 && color_teste <= 255)
		ref->red = color_teste;
	color_teste = ft_atoi(split[1]);
	if (color_teste >= 0 && color_teste <= 255)
		ref->green = color_teste;
	color_teste = ft_atoi(split[2]);
	if (color_teste >= 0 && color_teste <= 255)
		ref->blue = color_teste;
	free_array(split);
	return (true);
}

bool	fill_texture(void *mlx, t_img *tex, char *file)
{
	
	tex->img_ptr = mlx_xpm_file_to_image(mlx, file, &tex->width,
			&tex->height);
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
		
		line[ft_strlen(line) - 1] = '\0'; //remove the ending newline (this is guarranteed to be there)
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

bool	is_map_line(const char *line, char *allowed)
{
	int	i;
	int	j;
	int	allowed_count;

	j = -1;
	allowed_count = 0;
	while (line[++j])
	{
		if (line[j] == ' ')
			continue ;
		i = -1;
		while (allowed[++i])
		{
			if (line[j] == allowed[i])
			{
				allowed_count++;
				break ;
			}
		}
		if (!allowed[i])
			return (false);
	}
	return (allowed_count != 0);
}

